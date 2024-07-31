#include "ctpch.h"
#include "OpenGLInput.hpp"

#include "CherryTree/Core/Logging.hpp"

#include <GLFW/glfw3.h>

namespace Ct
{

	Input<RenderingAPI::OpenGL>::Input(void* window)
		: m_Window(window)
	{
	}

	bool Input<RenderingAPI::OpenGL>::IsKeyPressed(Key keycode)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(m_Window);

		int state = glfwGetKey(window, (int)keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input<RenderingAPI::OpenGL>::IsMousePressed(MouseButton button)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(m_Window);

		int state = glfwGetMouseButton(window, (int)button);
		return state == GLFW_PRESS;
	}

	glm::vec2 Input<RenderingAPI::OpenGL>::GetCursorPosition()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(m_Window);

		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		return { xPos, yPos };
	}

	void Input<RenderingAPI::OpenGL>::SetCursorPosition(glm::vec2 position)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(m_Window);

		glfwSetCursorPos(window, position.x, position.y);
	}

	void Input<RenderingAPI::OpenGL>::SetCursorMode(CursorMode mode)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(m_Window);

		glfwSetInputMode(window, GLFW_CURSOR, (int)mode);
	}

}