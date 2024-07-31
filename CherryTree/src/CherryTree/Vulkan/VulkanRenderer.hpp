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
	class Renderer<RenderingAPI::Vulkan> : public RefCounted
	{
	public:
		Renderer(Ref<GraphicsContext<RenderingAPI::Vulkan>> context);
		~Renderer();

		void Present();

	private:
		Ref<GraphicsContext<RenderingAPI::Vulkan>> m_Context;

		friend class GraphicsContext<RenderingAPI::Vulkan>;
	};

}