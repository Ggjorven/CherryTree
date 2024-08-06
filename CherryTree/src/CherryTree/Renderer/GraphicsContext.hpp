#pragma once

#include "CherryTree/Core/Memory.hpp"

#include "CherryTree/Renderer/RendererSpecification.hpp"

#include "CherryTree/OpenGL/OpenGLContext.hpp"
#include "CherryTree/Vulkan/VulkanContext.hpp"

namespace Ct
{

	// Note: This does nothing, it just shows the class
	template<RenderingAPI API>
	class GraphicsContext;

}