#include "ctpch.h"
#include "OpenGLContext.hpp"

#include "CherryTree/Core/Logging.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Ct
{

	uint32_t GraphicsContext<RenderingAPI::OpenGL>::s_OpenGLUsers = 0;

	void GraphicsContext<RenderingAPI::OpenGL>::Init()
	{
		CT_ASSERT((s_OpenGLUsers == 1), "OpenGL is already initialized.");

		int result = gladLoadGLLoader((GLADloadproc)&glfwGetProcAddress);
		CT_ASSERT(result, "Failed to initialize GLAD.");
	}

	void GraphicsContext<RenderingAPI::OpenGL>::Destroy()
	{
		CT_ASSERT((s_OpenGLUsers == 0), "Tried to destroy OpenGL while it is still being used.");
	}

}