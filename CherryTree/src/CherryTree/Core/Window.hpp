#pragma once

#include "CherryTree/Core/Memory.hpp"
#include "CherryTree/Core/Events.hpp"

#include "CherryTree/Renderer/RendererSpecification.hpp"

#include "CherryTree/Core/WindowSpecs.hpp"

#include "CherryTree/OpenGL/OpenGLWindow.hpp"
#include "CherryTree/Vulkan/VulkanWindow.hpp"

namespace Ct
{

	// Note: This doesn't do anything, it just shows the class
	template<RenderingAPI API>
	class Window; // Window closes on destructor.

}