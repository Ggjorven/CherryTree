#pragma once

#include "CherryTree/Core/Memory.hpp"

#include "CherryTree/Renderer/RendererSpecification.hpp"

#include "CherryTree/Vulkan/VulkanDevice.hpp"
#include "CherryTree/Vulkan/VulkanPhysicalDevice.hpp"

#include <vulkan/vulkan.h>

#include <cstdint>
#include <utility>

namespace Ct
{

	template<RenderingAPI API>
	class GraphicsContext;

	template<RenderingAPI API>
	class Renderer;



	template<>
	class GraphicsContext<RenderingAPI::Vulkan>
	{
	///////////////////////////////////////////////////////////
	// Core functionality
	///////////////////////////////////////////////////////////
	public:
		static void CreateInstance();
		static void CreateDevices(const VkSurfaceKHR surface);
		static void Destroy();

		inline static uint32_t IncUsers() { return ++s_VulkanUsers; }
		inline static uint32_t DecUsers() { return --s_VulkanUsers; }

		inline static const VkInstance GetVkInstance() { return s_VulkanInstance; }
		inline static const VkDebugUtilsMessengerEXT GetVkDebugger() { return s_DebugMessenger; }

		inline static Ref<VulkanPhysicalDevice> GetPhysicalDevice() { return s_PhysicalDevice; }
		inline static Ref<VulkanDevice> GetDevice() { return s_Device; }

	///////////////////////////////////////////////////////////
	// Private variables
	///////////////////////////////////////////////////////////
	private:
		static VkInstance s_VulkanInstance;
		static VkDebugUtilsMessengerEXT s_DebugMessenger;
		
		static Ref<VulkanPhysicalDevice> s_PhysicalDevice;
		static Ref<VulkanDevice> s_Device;

		static uint32_t s_VulkanUsers; // Amount of windows using these functionalities
		friend class Renderer<RenderingAPI::Vulkan>;

	///////////////////////////////////////////////////////////
	// Config variables
	///////////////////////////////////////////////////////////
	public:
		#if !defined(CT_CONFIG_DIST)
			static constexpr const bool s_Validation = true;
		#else
			static constexpr const bool s_Validation = false;
		#endif

		static const std::vector<const char*> s_RequestedValidationLayers;
		static const std::vector<const char*> s_RequestedDeviceExtensions;

		inline static constinit const std::pair<uint8_t, uint8_t> Version = { 1, 3 }; // Vulkan version 1.3.XXX
	};

}