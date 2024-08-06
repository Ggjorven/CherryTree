#pragma once

#include "CherryTree/Core/Memory.hpp"

#include "CherryTree/Renderer/RendererSpecification.hpp"

// TODO: OpenGL
#include "CherryTree/Vulkan/VulkanAllocator.hpp"

namespace Ct
{

	// Note: This does nothing, it just shows the class
	template<RenderingAPI API>
	class Allocator;

}