#pragma once

#include "CherryTree/Renderer/GraphicsContext.hpp"

namespace Ct
{

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(void* window);
		~OpenGLContext();
	};

}