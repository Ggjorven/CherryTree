#include "ctpch.h"
#include "OpenGLContext.hpp"

#include "CherryTree/Core/Logging.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Ct
{

	GraphicsContext<RenderingAPI::OpenGL>::GraphicsContext(void* window)
	{
		int result = gladLoadGLLoader((GLADloadproc)&glfwGetProcAddress);
		CT_ASSERT(result, "Failed to initialize GLAD.");
	}

	GraphicsContext<RenderingAPI::OpenGL>::~GraphicsContext()
	{
	}

}