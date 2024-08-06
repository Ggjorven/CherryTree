#include "ctpch.h"
#include "VulkanCommandBuffer.hpp"

#include "CherryTree/Core/Logging.hpp"

#include "CherryTree/Vulkan/VulkanUtils.hpp"
#include "CherryTree/Vulkan/VulkanContext.hpp"
#include "CherryTree/Vulkan/VulkanAllocator.hpp"

namespace Ct
{

	CommandBuffer<RenderingAPI::Vulkan>::CommandBuffer(const uint8_t framesInFlight, const VkCommandPool pool) // TODO: Create
	{
		/*
		auto device = GraphicsContext<RenderingAPI::Vulkan>::GetDevice()->GetVkDevice();
		const uint32_t framesInFlight = (uint32_t)renderer->GetSpecification().Buffers;
		m_CommandBuffers.resize(framesInFlight);

		VkCommandBufferAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		//allocInfo.commandPool = renderer->GetSwapChain()->GetVkCommandPool(); // TODO: ...
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount = (uint32_t)m_CommandBuffers.size();

		VK_CHECK_RESULT(vkAllocateCommandBuffers(device, &allocInfo, m_CommandBuffers.data()));

		m_RenderFinishedSemaphores.resize(framesInFlight);
		m_InFlightFences.resize(framesInFlight);

		VkSemaphoreCreateInfo semaphoreInfo = {};
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		VkFenceCreateInfo fenceInfo = {};
		fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		for (size_t i = 0; i < framesInFlight; i++)
		{
			VK_CHECK_RESULT(vkCreateSemaphore(device, &semaphoreInfo, nullptr, &m_RenderFinishedSemaphores[i]));
			VK_CHECK_RESULT(vkCreateFence(device, &fenceInfo, nullptr, &m_InFlightFences[i]));
		}
		*/
	}

	CommandBuffer<RenderingAPI::Vulkan>::~CommandBuffer() // Note: This doesn't free the commandBuffer, we leave that up to the commandPool destruction (might not be the best choice)
	{
		/*
		auto device = GraphicsContext<RenderingAPI::Vulkan>::GetDevice();
		vkDeviceWaitIdle(device->GetVkDevice());

		for (size_t i = 0; i < m_RenderFinishedSemaphores.size(); i++)
		{
			vkDestroySemaphore(device->GetVkDevice(), m_RenderFinishedSemaphores[i], nullptr);
			vkDestroyFence(device->GetVkDevice(), m_InFlightFences[i], nullptr);
		}
		*/
	}



	VulkanCommand::VulkanCommand(const VkCommandPool commandPool, bool start)
		: m_CommandPool(commandPool)
	{
		VkCommandBufferAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = m_CommandPool;
		allocInfo.commandBufferCount = 1;

		VK_CHECK_RESULT(vkAllocateCommandBuffers(GraphicsContext<RenderingAPI::Vulkan>::GetDevice()->GetVkDevice(), &allocInfo, &m_CommandBuffer));

		if (start)
			Begin();
	}

	VulkanCommand::~VulkanCommand()
	{
		vkFreeCommandBuffers(GraphicsContext<RenderingAPI::Vulkan>::GetDevice()->GetVkDevice(), m_CommandPool, 1, &m_CommandBuffer);
	}

	void VulkanCommand::Begin()
	{
		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

		vkBeginCommandBuffer(m_CommandBuffer, &beginInfo);
	}

	void VulkanCommand::End()
	{
		vkEndCommandBuffer(m_CommandBuffer);
	}

	void VulkanCommand::Submit()
	{
		VkSubmitInfo submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &m_CommandBuffer;

		vkQueueSubmit(GraphicsContext<RenderingAPI::Vulkan>::GetDevice()->GetGraphicsQueue(), 1, &submitInfo, VK_NULL_HANDLE);
		vkQueueWaitIdle(GraphicsContext<RenderingAPI::Vulkan>::GetDevice()->GetGraphicsQueue());
	}

	void VulkanCommand::EndAndSubmit()
	{
		End();
		Submit();
	}

}