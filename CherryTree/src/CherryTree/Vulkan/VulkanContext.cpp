#include "ctpch.h"
#include "VulkanContext.hpp"

#include "CherryTree/Core/Logging.hpp"

#include "CherryTree/Vulkan/VulkanUtils.hpp"
#include "CherryTree/Vulkan/VulkanAllocator.hpp"

#include <vulkan/vulkan.h>

///////////////////////////////////////////////////////////
// Helper functions
///////////////////////////////////////////////////////////
static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
	const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger)
{
	auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

	if (func != nullptr)
		return func(instance, pCreateInfo, pAllocator, pDebugMessenger);

	return VK_ERROR_EXTENSION_NOT_PRESENT;
}

static void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator)
{
	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");

	if (func != nullptr)
		func(instance, debugMessenger, pAllocator);
}

static VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
{
	if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
	{
		CT_LOG_WARN("Validation layer: {0}", pCallbackData->pMessage);
		return VK_FALSE;
	}

	return VK_FALSE;
}

bool ValidationLayersSupported()
{
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    // Check if all requested layers are actually accessible
    for (const char* layerName : Ct::GraphicsContext<Ct::RenderingAPI::Vulkan>::s_RequestedValidationLayers)
    {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers)
        {
            if (strcmp(layerName, layerProperties.layerName) == 0)
            {
                layerFound = true;
                break;
            }
        }

        if (!layerFound)
            return false;
    }

    return true;
}

namespace Ct
{

	VkInstance GraphicsContext<RenderingAPI::Vulkan>::s_VulkanInstance = VK_NULL_HANDLE;
	VkDebugUtilsMessengerEXT GraphicsContext<RenderingAPI::Vulkan>::s_DebugMessenger = VK_NULL_HANDLE;

	Ref<VulkanPhysicalDevice> GraphicsContext<RenderingAPI::Vulkan>::s_PhysicalDevice = nullptr;
	Ref<VulkanDevice> GraphicsContext<RenderingAPI::Vulkan>::s_Device = nullptr;

	uint32_t GraphicsContext<RenderingAPI::Vulkan>::s_VulkanUsers = 0;

	const std::vector<const char*> GraphicsContext<RenderingAPI::Vulkan>::s_RequestedValidationLayers = { "VK_LAYER_KHRONOS_validation" };
	const std::vector<const char*> GraphicsContext<RenderingAPI::Vulkan>::s_RequestedDeviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };



	void GraphicsContext<RenderingAPI::Vulkan>::CreateInstance()
	{
		CT_ASSERT((s_VulkanUsers == 1), "Vulkan has already been initialized");

		///////////////////////////////////////////////////////////
		// Instance Creation
		///////////////////////////////////////////////////////////
		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "CherryTree Application";
		appInfo.applicationVersion = VK_MAKE_API_VERSION(0, Version.first, Version.second, 0);
		appInfo.pEngineName = "CherryTree Engine";
		appInfo.engineVersion = VK_MAKE_API_VERSION(0, Version.first, Version.second, 0);
		appInfo.apiVersion = VK_MAKE_API_VERSION(0, Version.first, Version.second, 0);

		#if defined(CT_PLATFORM_WINDOWS)
			#define VK_KHR_WIN32_SURFACE_EXTENSION_NAME "VK_KHR_win32_surface"
		#elif defined(CT_PLATFORM_LINUX)
			#define VK_KHR_WIN32_SURFACE_EXTENSION_NAME "VK_KHR_xcb_surface"
		#endif // TODO: MacOS

		std::vector<const char*> instanceExtensions = { VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_WIN32_SURFACE_EXTENSION_NAME };
		if constexpr (s_Validation)
		{
            if (!ValidationLayersSupported())
            {
                CT_LOG_ERROR("Validation layers are not supported!");
            }
            else
            {
                instanceExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME); // Very little performance hit, can be used in Release.
                instanceExtensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
                instanceExtensions.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
            }
		}

        #if defined(CT_PLATFORM_MACOS)
        instanceExtensions.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
        #endif

		VkInstanceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;
		#if defined(CT_PLATFORM_MACOS)
			createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
		#endif
		createInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());
		createInfo.ppEnabledExtensionNames = instanceExtensions.data();

		if constexpr (s_Validation)
		{
            if (ValidationLayersSupported())
            {
			    createInfo.enabledLayerCount = static_cast<uint32_t>(s_RequestedValidationLayers.size());
			    createInfo.ppEnabledLayerNames = s_RequestedValidationLayers.data();
            }
		}
		else
		{
			createInfo.enabledLayerCount = 0;
		}

		// Note(Jorben): Setup the debug messenger also for the create instance
		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {};
		debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		debugCreateInfo.pfnUserCallback = VulkanDebugCallback;

		if constexpr (s_Validation)
		{
            if (ValidationLayersSupported())
            {
			    createInfo.enabledLayerCount = static_cast<uint32_t>(s_RequestedValidationLayers.size());
			    createInfo.ppEnabledLayerNames = s_RequestedValidationLayers.data();

			    createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
            }
		}
		else
		{
			createInfo.enabledLayerCount = 0;
			createInfo.pNext = nullptr;
		}

		VK_CHECK_RESULT(vkCreateInstance(&createInfo, nullptr, &s_VulkanInstance));

		///////////////////////////////////////////////////////////
		// Debugger Creation
		///////////////////////////////////////////////////////////
		if constexpr (s_Validation)
		{
            if (ValidationLayersSupported())
            {
			    VK_CHECK_RESULT(CreateDebugUtilsMessengerEXT(s_VulkanInstance, &debugCreateInfo, nullptr, &s_DebugMessenger));
            }
        }
	}

	void GraphicsContext<RenderingAPI::Vulkan>::CreateDevices(const VkSurfaceKHR surface)
	{
		CT_ASSERT((s_VulkanUsers == 1), "Vulkan has already been initialized");

		///////////////////////////////////////////////////////////
		// Other
		///////////////////////////////////////////////////////////
		s_PhysicalDevice = VulkanPhysicalDevice::Select(surface);
		s_Device = VulkanDevice::Create(surface, s_PhysicalDevice);

		Allocator<RenderingAPI::Vulkan>::Init();
	}

	void GraphicsContext<RenderingAPI::Vulkan>::Destroy()
	{
		CT_ASSERT((s_VulkanUsers == 0), "Tried to destroy Vulkan while it is still being used.");

		s_Device->Wait();

		Allocator<RenderingAPI::Vulkan>::Destroy();

        s_PhysicalDevice.Reset();
		s_Device.Reset();

		if constexpr (s_Validation)
        {
            if (s_DebugMessenger)
			    DestroyDebugUtilsMessengerEXT(s_VulkanInstance, s_DebugMessenger, nullptr);
        }

		vkDestroyInstance(s_VulkanInstance, nullptr);
	}

}
