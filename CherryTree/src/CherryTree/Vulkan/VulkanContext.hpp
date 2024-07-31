#pragma once

#include "CherryTree/Core/Memory.hpp"

#include "CherryTree/Renderer/RendererSpecification.hpp"

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
	class GraphicsContext<RenderingAPI::Vulkan> : public RefCounted
	{
	///////////////////////////////////////////////////////////
	// Core functionality
	///////////////////////////////////////////////////////////
	public:
		GraphicsContext(void* window, const RendererSpecification& specs);
		~GraphicsContext();

		inline const RendererSpecification& GetSpecification() const { return m_Specification; }

		inline const VkInstance GetVkInstance() const { return m_VulkanInstance; }
		inline const VkDebugUtilsMessengerEXT GetVkDebugger() const { return m_DebugMessenger; }
		inline const VkSurfaceKHR GetVkSurface() const { return m_Surface; }

	///////////////////////////////////////////////////////////
	// Private variables
	///////////////////////////////////////////////////////////
	private:
		void* m_Window;
		RendererSpecification m_Specification;

		VkInstance m_VulkanInstance = VK_NULL_HANDLE;
		VkDebugUtilsMessengerEXT m_DebugMessenger = VK_NULL_HANDLE;
		VkSurfaceKHR m_Surface = VK_NULL_HANDLE;

		//Ref<VulkanPhysicalDevice> m_PhysicalDevice = VK_NULL_HANDLE;
		//Ref<VulkanDevice> m_Device = VK_NULL_HANDLE;
		//Ref<VulkanSwapChain> m_SwapChain = VK_NULL_HANDLE;

		friend class Renderer<RenderingAPI::Vulkan>;

	///////////////////////////////////////////////////////////
	// Static variables
	///////////////////////////////////////////////////////////
	public:
		#if !defined(CT_CONFIG_DIST)
			static constexpr bool s_Validation = true;
		#else
			static constexpr bool s_Validation = false;
		#endif

		static const std::vector<const char*> s_RequestedValidationLayers;
		static const std::vector<const char*> s_RequestedDeviceExtensions;

		inline static constinit const std::pair<uint8_t, uint8_t> Version = { 1, 3 }; // Vulkan version 1.3.XXX
	};

}