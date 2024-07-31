#pragma once

#include "CherryTree/Core/Memory.hpp"

#include "CherryTree/Renderer/RendererSpecification.hpp"

#include <cstdint>
#include <utility>

namespace Ct
{

	template<RenderingAPI API>
	class GraphicsContext;

	template<RenderingAPI API>
	class Renderer;


	
	template<>
	class GraphicsContext<RenderingAPI::OpenGL> : public RefCounted
	{
	public:
		GraphicsContext(void* window, const RendererSpecification& specs);
		~GraphicsContext();

		inline const RendererSpecification& GetSpecification() const { return m_Specification; }

	private:
		// Core
		void* m_Window;
		RendererSpecification m_Specification;

		friend class Renderer<RenderingAPI::OpenGL>;

    public:
		inline static constinit const std::pair<uint8_t, uint8_t> Version = { 4, 5 }; // OpenGL version 4.5 (Core)
	};

}