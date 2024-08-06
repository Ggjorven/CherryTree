#include "ctpch.h"
#include "VulkanRenderer.hpp"

#include "CherryTree/Core/Logging.hpp"

#include "CherryTree/Vulkan/VulkanContext.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Ct
{

	Renderer<RenderingAPI::Vulkan>::Renderer(void* window, const RendererSpecification& specs, const VkSurfaceKHR surface)
		: m_Window(window), m_Specification(specs), m_Surface(surface)
	{
	}

	Renderer<RenderingAPI::Vulkan>::~Renderer()
	{
	}

	void Renderer<RenderingAPI::Vulkan>::Init(uint32_t width, uint32_t height)
	{
		m_Allocator = Ref<Allocator<RenderingAPI::Vulkan>>::Create((uint8_t)m_Specification.Buffers);

		// TODO: Create swapchain
		m_SwapChain = Ref<VulkanSwapChain>::Create(m_Allocator, m_Surface, (uint8_t)m_Specification.Buffers);
	}

	void Renderer<RenderingAPI::Vulkan>::Present()
	{
	}

}