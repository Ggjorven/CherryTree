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
	///////////////////////////////////////////////////////////
	// Core functionality
	///////////////////////////////////////////////////////////
	public:
		static void Init();
		static void Destroy();

		inline static uint32_t IncUsers() { return ++s_OpenGLUsers; }
		inline static uint32_t DecUsers() { return --s_OpenGLUsers; }

	///////////////////////////////////////////////////////////
	// Private variables
	///////////////////////////////////////////////////////////
	private:
		static uint32_t s_OpenGLUsers; // Amount of windows using these functionalities

		friend class Renderer<RenderingAPI::OpenGL>;

	///////////////////////////////////////////////////////////
	// Config variables
	///////////////////////////////////////////////////////////
    public:
		inline static constinit const std::pair<uint8_t, uint8_t> Version = { 4, 5 }; // OpenGL version 4.5 (Core)
	};

}