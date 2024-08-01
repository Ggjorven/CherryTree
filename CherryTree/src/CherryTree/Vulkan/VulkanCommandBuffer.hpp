#pragma once

#include "CherryTree/Core/Memory.hpp"

#include "CherryTree/Renderer/RendererSpecification.hpp"

#include "CherryTree/Vulkan/VulkanContext.hpp"

#include <vector>

#include <vulkan/vulkan.h>

namespace Ct
{

	template<RenderingAPI API>
	class CommandBuffer;



	template<>
	class CommandBuffer<RenderingAPI::Vulkan> : public RefCounted
	{
	public:
		CommandBuffer(Ref<GraphicsContext<RenderingAPI::Vulkan>> context);
		virtual ~CommandBuffer();

		void Begin();
		void End();

		inline const VkSemaphore GetVkRenderFinishedSemaphore(uint32_t index) const { return m_RenderFinishedSemaphores[index]; }
		inline const VkFence GetVkInFlightFence(uint32_t index) const { return m_InFlightFences[index]; }
		inline const VkCommandBuffer GetVkCommandBuffer(uint32_t index) const { return m_CommandBuffers[index]; }

	private:
		std::vector<VkCommandBuffer> m_CommandBuffers = { };

		// Syncronization objects
		std::vector<VkSemaphore> m_RenderFinishedSemaphores = { };
		std::vector<VkFence> m_InFlightFences = { };
	};



	class VulkanCommand // For running simple commands
	{
	public:
		VulkanCommand(Ref<GraphicsContext<RenderingAPI::Vulkan>> context, bool start = false);
		virtual ~VulkanCommand();

		void Begin();
		void End();
		void Submit();
		void EndAndSubmit();

		inline const VkCommandBuffer GetVulkanCommandBuffer() const { return m_CommandBuffer; }

	private:
		Ref<GraphicsContext<RenderingAPI::Vulkan>> m_Context;
		VkCommandBuffer m_CommandBuffer = VK_NULL_HANDLE;
	};

}