#pragma once

#include "CherryTree/Core/Memory.hpp"

#include "CherryTree/Renderer/RendererSpecification.hpp"

#include <cstdint>
#include <utility>

namespace Ct
{

	template<RenderingAPI API>
	class Renderer;

	template<RenderingAPI API>
	class GraphicsContext;

	template<>
	class Renderer<RenderingAPI::OpenGL> : public RefCounted
	{
	public:
		Renderer(Ref<GraphicsContext<RenderingAPI::OpenGL>> context);
		~Renderer();

	private:
		Ref<GraphicsContext<RenderingAPI::OpenGL>> m_Context;

		friend class GraphicsContext<RenderingAPI::OpenGL>;
	};

}