#pragma once

#include "CherryTree/Renderer/RendererSpecification.hpp"

#include <cstdint>
#include <utility>

namespace Ct
{

	template<RenderingAPI API>
	class GraphicsContext;

	template<>
	class GraphicsContext<RenderingAPI::Vulkan>
	{
	public:
		GraphicsContext(void* window);
		~GraphicsContext();
	};

}