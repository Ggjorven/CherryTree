#include "ctpch.h"
#include "OpenGLRenderer.hpp"

#include "CherryTree/Core/Logging.hpp"

#include "CherryTree/OpenGL/OpenGLContext.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Ct
{

	Renderer<RenderingAPI::OpenGL>::Renderer(void* window, const RendererSpecification& specs)
		: m_Window(window), m_Specification(specs)
	{
	}

	Renderer<RenderingAPI::OpenGL>::~Renderer()
	{
	}

	void Renderer<RenderingAPI::OpenGL>::Init()
	{
		glfwSwapInterval(m_Specification.VSync);
	}

}