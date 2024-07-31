#include "ctpch.h"
#include "OpenGLRenderer.hpp"

#include "CherryTree/Core/Logging.hpp"

#include "CherryTree/OpenGL/OpenGLContext.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Ct
{

	Renderer<RenderingAPI::OpenGL>::Renderer(Ref<GraphicsContext<RenderingAPI::OpenGL>> context)
		: m_Context(context)
	{
	}

	Renderer<RenderingAPI::OpenGL>::~Renderer()
	{
	}

}