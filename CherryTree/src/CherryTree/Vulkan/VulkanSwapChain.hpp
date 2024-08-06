#pragma once

#include "CherryTree/Core/Memory.hpp"

#include "CherryTree/Renderer/RendererSpecification.hpp"

#include "CherryTree/Vulkan/VulkanImage.hpp"
#include "CherryTree/Vulkan/VulkanAllocator.hpp"

#include <vulkan/vulkan.h>

#include <cstdint>
#include <utility>

namespace Ct
{

	class VulkanSwapChain : public RefCounted
	{
	public:
		VulkanSwapChain(Ref<Allocator<RenderingAPI::Vulkan>> allocator, const VkSurfaceKHR surface, const uint8_t framesInFlight);
		~VulkanSwapChain();

		void Init(uint32_t width, uint32_t height, const bool vsync);

		inline const VkFormat GetColourFormat() const { return m_ColourFormat; }

		inline uint32_t GetCurrentFrame() const { return m_CurrentFrame; }
		inline uint32_t GetAquiredImage() const { return m_AquiredImage; }

		inline std::vector<Ref<Image<RenderingAPI::Vulkan>>>& GetSwapChainImages() { return m_Images; }
		inline Ref<Image<RenderingAPI::Vulkan>> GetDepthImage() { return m_DepthStencil; }

		// Note(Jorben): This function is used by VulkanRenderCommandBuffers to wait for the image to be available
		inline const VkSemaphore GetCurrentImageAvailableSemaphore() const { return m_ImageAvailableSemaphores[m_CurrentFrame]; }
		inline const VkSemaphore GetImageAvailableSemaphore(uint32_t index) const { return m_ImageAvailableSemaphores[index]; }
		inline const VkCommandPool GetCommandPool() const { return m_CommandPool; }

	private:
		uint32_t AcquireNextImage();
		void FindImageFormatAndColorSpace();

	private:
		VkSwapchainKHR m_SwapChain = VK_NULL_HANDLE;

		std::vector<Ref<Image<RenderingAPI::Vulkan>>> m_Images = { };
		Ref<Image<RenderingAPI::Vulkan>> m_DepthStencil = nullptr;

		VkCommandPool m_CommandPool = VK_NULL_HANDLE;

		std::vector<VkSemaphore> m_ImageAvailableSemaphores = { };

		VkFormat m_ColourFormat = VK_FORMAT_UNDEFINED;
		VkColorSpaceKHR m_ColourSpace = VK_COLOR_SPACE_MAX_ENUM_KHR;

		uint32_t m_CurrentFrame = 0;
		uint32_t m_AquiredImage = 0;

		const VkSurfaceKHR m_Surface;
		const uint8_t m_FramesInFlight;
	};

}