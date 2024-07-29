#pragma once

#include "CherryTree/Core/Memory.hpp"

#include "CherryTree/Renderer/RendererSpecification.hpp"

namespace Ct
{

	class GraphicsContext
	{
	public:
		GraphicsContext() = default;
		virtual ~GraphicsContext() = default;
		
		static Unique<GraphicsContext> Create(const RenderingAPI api, void* window);
	};

}