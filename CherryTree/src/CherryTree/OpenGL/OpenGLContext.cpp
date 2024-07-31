#include "ctpch.h"
#include "OpenGLContext.hpp"

#include "CherryTree/Core/Logging.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Ct
{

	GraphicsContext<RenderingAPI::OpenGL>::GraphicsContext(void* window, const RendererSpecification& specs)
		: m_Window(window), m_Specification(specs)
	{
		int result = gladLoadGLLoader((GLADloadproc)&glfwGetProcAddress);
		CT_ASSERT(result, "Failed to initialize GLAD.");

		glfwSwapInterval(specs.VSync);
	}

	GraphicsContext<RenderingAPI::OpenGL>::~GraphicsContext()
	{
	}

}