#include "ctpch.h"
#include "VulkanRenderer.hpp"

#include "CherryTree/Core/Logging.hpp"

#include "CherryTree/Vulkan/VulkanContext.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Ct
{

	Renderer<RenderingAPI::Vulkan>::Renderer(Ref<GraphicsContext<RenderingAPI::Vulkan>> context)
		: m_Context(context)
	{
	}

	Renderer<RenderingAPI::Vulkan>::~Renderer()
	{
	}

	void Renderer<RenderingAPI::Vulkan>::Present()
	{
	}

}