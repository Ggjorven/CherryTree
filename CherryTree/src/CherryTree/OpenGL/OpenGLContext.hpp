#pragma once

#include "CherryTree/Renderer/RendererSpecification.hpp"

#include <cstdint>
#include <utility>

namespace Ct
{

	template<RenderingAPI API>
	class GraphicsContext;

	template<>
	class GraphicsContext<RenderingAPI::OpenGL>
	{
	public:
		GraphicsContext(void* window);
		~GraphicsContext();

    public:
		inline static constinit const std::pair<uint8_t, uint8_t> Version = { 4, 5 };
	};

}