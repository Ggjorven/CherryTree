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

	void Renderer<RenderingAPI::Vulkan>::Init()
	{
	}

	void Renderer<RenderingAPI::Vulkan>::Present()
	{
	}

}