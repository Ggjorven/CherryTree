#pragma once

#include "CherryTree/Core/Memory.hpp"

#include "CherryTree/Renderer/RendererSpecification.hpp"

#include "CherryTree/Vulkan/VulkanImage.hpp"
#include "CherryTree/Vulkan/VulkanCommandBuffer.hpp"

#include <vulkan/vulkan.h>
#include <vk_mem_alloc.h>

namespace Ct
{

	template<RenderingAPI API>
	class Allocator;

	template<RenderingAPI API>
	class Renderer;

	class VulkanSwapChain;



	template<>
	class Allocator<RenderingAPI::Vulkan> : public RefCounted
	{
	public:
		static void Init();
		static void Destroy();

	public:
		Allocator(const uint8_t framesInFlight);
		~Allocator();

		Ref<Image<RenderingAPI::Vulkan>> AllocImage(const ImageSpecification& specs);
		Ref<CommandBuffer<RenderingAPI::Vulkan>> AllocCmdBuf();

	private:
		const uint8_t m_FramesInFlight;
		VkCommandPool m_CommandPool; // Reference to the swapchain commandpool

		friend class VulkanSwapChain;
		friend class Renderer<RenderingAPI::Vulkan>;

        friend class Image<RenderingAPI::Vulkan>;
        friend class CommandBuffer<RenderingAPI::Vulkan>;
	};

}
