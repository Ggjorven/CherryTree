#include "ctpch.h"
#include "VulkanDevice.hpp"

#include "CherryTree/Core/Logging.hpp"

#include "CherryTree/Vulkan/VulkanUtils.hpp"
#include "CherryTree/Vulkan/VulkanContext.hpp"

namespace Ct
{

	VulkanDevice::VulkanDevice(const VkSurfaceKHR surface, Ref<VulkanPhysicalDevice> physicalDevice)
		: m_PhysicalDevice(physicalDevice)
	{
		QueueFamilyIndices indices = QueueFamilyIndices::Find(surface, m_PhysicalDevice->GetVkPhysicalDevice());

		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::set<uint32_t> uniqueQueueFamilies = { indices.GraphicsFamily.value(), indices.PresentFamily.value() };

		float queuePriority = 1.0f;
		for (uint32_t queueFamily : uniqueQueueFamilies)
		{
			VkDeviceQueueCreateInfo queueCreateInfo = {};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = queueFamily;
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &queuePriority;
			queueCreateInfos.push_back(queueCreateInfo);
		}

		VkPhysicalDeviceFeatures deviceFeatures = {};
		deviceFeatures.samplerAnisotropy = VK_TRUE;
		deviceFeatures.fillModeNonSolid = VK_TRUE;
		deviceFeatures.wideLines = VK_TRUE;

		VkDeviceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		createInfo.pQueueCreateInfos = queueCreateInfos.data();
		createInfo.pEnabledFeatures = &deviceFeatures;
		createInfo.enabledExtensionCount = static_cast<uint32_t>(GraphicsContext<RenderingAPI::Vulkan>::s_RequestedDeviceExtensions.size());
		createInfo.ppEnabledExtensionNames = GraphicsContext<RenderingAPI::Vulkan>::s_RequestedDeviceExtensions.data();

		if constexpr (GraphicsContext<RenderingAPI::Vulkan>::s_Validation)
		{
			createInfo.enabledLayerCount = static_cast<uint32_t>(GraphicsContext<RenderingAPI::Vulkan>::s_RequestedValidationLayers.size());
			createInfo.ppEnabledLayerNames = GraphicsContext<RenderingAPI::Vulkan>::s_RequestedValidationLayers.data();
		}
		else
		{
			createInfo.enabledLayerCount = 0;
		}

		VK_CHECK_RESULT(vkCreateDevice(m_PhysicalDevice->GetVkPhysicalDevice(), &createInfo, nullptr, &m_LogicalDevice));

		// Retrieve the graphics/compute/present queue handle
		vkGetDeviceQueue(m_LogicalDevice, indices.GraphicsFamily.value(), 0, &m_GraphicsQueue);
		vkGetDeviceQueue(m_LogicalDevice, indices.ComputeFamily.value(), 0, &m_ComputeQueue);
		vkGetDeviceQueue(m_LogicalDevice, indices.PresentFamily.value(), 0, &m_PresentQueue);
	}

	VulkanDevice::~VulkanDevice()
	{
		vkDestroyDevice(m_LogicalDevice, nullptr);
	}

	void VulkanDevice::Wait() const
	{
		vkDeviceWaitIdle(m_LogicalDevice);
	}

	Ref<VulkanDevice> VulkanDevice::Create(const VkSurfaceKHR surface, Ref<VulkanPhysicalDevice> physicalDevice)
	{
		return Ref<VulkanDevice>::Create(surface, physicalDevice);
	}

}