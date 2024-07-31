#include "ctpch.h"
#include "VulkanInput.hpp"

#include "CherryTree/Core/Logging.hpp"

#include <GLFW/glfw3.h>

namespace Ct
{

	Input<RenderingAPI::Vulkan>::Input(void* window)
		: m_Window(window)
	{
	}

	bool Input<RenderingAPI::Vulkan>::IsKeyPressed(Key keycode)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(m_Window);

		int state = glfwGetKey(window, (int)keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input<RenderingAPI::Vulkan>::IsMousePressed(MouseButton button)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(m_Window);

		int state = glfwGetMouseButton(window, (int)button);
		return state == GLFW_PRESS;
	}

	glm::vec2 Input<RenderingAPI::Vulkan>::GetCursorPosition()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(m_Window);

		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		return { xPos, yPos };
	}

	void Input<RenderingAPI::Vulkan>::SetCursorPosition(glm::vec2 position)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(m_Window);

		glfwSetCursorPos(window, position.x, position.y);
	}

	void Input<RenderingAPI::Vulkan>::SetCursorMode(CursorMode mode)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(m_Window);

		glfwSetInputMode(window, GLFW_CURSOR, (int)mode);
	}

}