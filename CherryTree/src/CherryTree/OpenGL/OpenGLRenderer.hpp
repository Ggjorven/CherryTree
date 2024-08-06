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
		Renderer(void* window, const RendererSpecification& specs);
		~Renderer();

		void Init();

		inline const RendererSpecification& GetSpecification() const { return m_Specification; }

	private:
		void* m_Window;
		RendererSpecification m_Specification;

		friend class GraphicsContext<RenderingAPI::OpenGL>;
	};

}