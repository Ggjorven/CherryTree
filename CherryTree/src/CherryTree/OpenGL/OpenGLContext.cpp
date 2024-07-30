#include "ctpch.h"
#include "OpenGLContext.hpp"

#include "CherryTree/Core/Logging.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Ct
{

	OpenGLContext::OpenGLContext(void* window)
	{
		int result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CT_ASSERT(result, "Failed to initialize GLAD.");
	}

	OpenGLContext::~OpenGLContext()
	{
	}

}