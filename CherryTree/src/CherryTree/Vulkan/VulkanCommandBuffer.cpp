#include "ctpch.h"
#include "VulkanCommandBuffer.hpp"

#include "CherryTree/Core/Logging.hpp"

#include "CherryTree/Vulkan/VulkanUtils.hpp"
#include "CherryTree/Vulkan/VulkanContext.hpp"

namespace Ct
{

	CommandBuffer<RenderingAPI::Vulkan>::CommandBuffer(Ref<GraphicsContext<RenderingAPI::Vulkan>> context) // TODO: Create
	{
	}

	CommandBuffer<RenderingAPI::Vulkan>::~CommandBuffer()
	{
	}

	void CommandBuffer<RenderingAPI::Vulkan>::Begin()
	{
	}

	void CommandBuffer<RenderingAPI::Vulkan>::End()
	{
	}



	VulkanCommand::VulkanCommand(Ref<GraphicsContext<RenderingAPI::Vulkan>> context, bool start)
		: m_Context(context)
	{
		/*
		VkCommandBufferAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = renderer->GetSwapChain()->GetCommandPool();
		allocInfo.commandBufferCount = 1;

		VK_CHECK_RESULT(vkAllocateCommandBuffers(renderer->GetLogicalDevice()->GetVulkanDevice(), &allocInfo, &m_CommandBuffer));

		if (start)
			Begin();
		*/
	}

	VulkanCommand::~VulkanCommand()
	{
		/*
		auto renderer = (VulkanRenderer*)Renderer::GetInstance();
		vkFreeCommandBuffers(renderer->GetLogicalDevice()->GetVulkanDevice(), renderer->GetSwapChain()->GetCommandPool(), 1, &m_CommandBuffer);
		*/
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
		/*
		auto renderer = (VulkanRenderer*)Renderer::GetInstance();

		VkSubmitInfo submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &m_CommandBuffer;

		vkQueueSubmit(renderer->GetLogicalDevice()->GetGraphicsQueue(), 1, &submitInfo, VK_NULL_HANDLE);
		vkQueueWaitIdle(renderer->GetLogicalDevice()->GetGraphicsQueue());
		*/
	}

	void VulkanCommand::EndAndSubmit()
	{
		End();
		Submit();
	}

}