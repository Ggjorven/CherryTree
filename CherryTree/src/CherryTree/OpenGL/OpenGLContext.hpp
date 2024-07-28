#pragma once

#include <iostream> // TODO: Remove

#include "CherryTree/Renderer/RenderingContext.hpp"

namespace Ct
{

	class OpenGLRenderingContext : public RenderingContext<OpenGLRenderingContext>
	{
	public:
		OpenGLRenderingContext() = default;
		~OpenGLRenderingContext() = default;

		void InitImpl() { std::cout << "OpenGL: Init" << std::endl; }
		void DestroyImpl() { std::cout << "OpenGL: Destroy" << std::endl; }
	};

}