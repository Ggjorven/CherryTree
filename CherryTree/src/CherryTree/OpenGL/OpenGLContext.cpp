#include "ctpch.h"
#include "OpenGLContext.hpp"

#include "CherryTree/Core/Logging.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Ct
{

	OpenGLContext::OpenGLContext(void* window)
	{
		CT_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize GLAD.");
	}

	OpenGLContext::~OpenGLContext()
	{
	}

}