#pragma once

#include "CherryTree/Core/Memory.hpp"

#include "CherryTree/Renderer/RendererSpecification.hpp"

#include <vulkan/vulkan.h>

#include <vector>

namespace Ct
{

	template<RenderingAPI API>
	class Allocator;

	template<RenderingAPI API>
	class CommandBuffer;



	template<>
	class CommandBuffer<RenderingAPI::Vulkan> : public RefCounted
	{
	public:
		virtual ~CommandBuffer();

		// The Begin, End & Submit methods are in the Renderer class.

		inline const VkSemaphore GetVkRenderFinishedSemaphore(uint32_t index) const { return m_RenderFinishedSemaphores[index]; }
		inline const VkFence GetVkInFlightFence(uint32_t index) const { return m_InFlightFences[index]; }
		inline const VkCommandBuffer GetVkCommandBuffer(uint32_t index) const { return m_CommandBuffers[index]; }

	private:
		CommandBuffer(const uint8_t framesInFlight, const VkCommandPool pool);

	private:
		std::vector<VkCommandBuffer> m_CommandBuffers = { };

		// Syncronization objects
		std::vector<VkSemaphore> m_RenderFinishedSemaphores = { };
		std::vector<VkFence> m_InFlightFences = { };

		friend class Allocator<RenderingAPI::Vulkan>;
	};



	class VulkanCommand // For running simple commands
	{
	public:
		VulkanCommand(const VkCommandPool commandPool, bool start = false);
		virtual ~VulkanCommand();

		void Begin();
		void End();
		void Submit();
		void EndAndSubmit();

		inline const VkCommandBuffer GetVulkanCommandBuffer() const { return m_CommandBuffer; }

	private:
		VkCommandPool m_CommandPool = VK_NULL_HANDLE; // Reference to the command pool (for the destructor)
		VkCommandBuffer m_CommandBuffer = VK_NULL_HANDLE;
	};

}