#include "ctpch.h"
#include "LinuxWindow.hpp"

#include "CherryTree/Core/Logging.hpp"

namespace Ct
{

	static uint32_t s_Instances = 0u;
	static bool s_GLFWinitialized = false;

	static void GLFWErrorCallBack(int errorCode, const char* description)
	{
		CT_LOG_ERROR("[GLFW]: ({0}), {1}", errorCode, description);
	}



	LinuxWindow::LinuxWindow(const WindowSpecification windowSpecs, const RendererSpecification rendererSpecs)
		: m_WindowData(windowSpecs), m_RendererSpecs(rendererSpecs)
	{
		CT_ASSERT(m_WindowData.EventCallback, "No event callback was passed in.");

		// TODO: Renderer

		if (!s_GLFWinitialized)
		{
			int succes = glfwInit();
			if (!succes)
				CT_LOG_ERROR("(GLFW) glfwInit() failed");

			s_GLFWinitialized = true;
			glfwSetErrorCallback(GLFWErrorCallBack);
		}

		if (rendererSpecs.API == RenderingAPI::Vulkan) glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		m_Window = glfwCreateWindow((int)windowSpecs.Width, (int)windowSpecs.Height, windowSpecs.Title.c_str(), nullptr, nullptr);
		s_Instances++;

		glfwSetWindowUserPointer(m_Window, (void*)&m_WindowData); //So we can access/get to the data in lambda functions

		// Event system
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				LinuxWindowData& data = *(LinuxWindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				if (width > 0 || height > 0)
					data.Closed = false;
				else
					data.Closed = true;

				WindowResizeEvent event = WindowResizeEvent(width, height);
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				LinuxWindowData& data = *(LinuxWindowData*)glfwGetWindowUserPointer(window);
				data.Closed = true;

				WindowCloseEvent event = WindowCloseEvent();
				data.EventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				LinuxWindowData& data = *(LinuxWindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event = KeyPressedEvent(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event = KeyReleasedEvent(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event = KeyPressedEvent(key, 1);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
			{
				LinuxWindowData& data = *(LinuxWindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event = KeyTypedEvent(keycode);
				data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				LinuxWindowData& data = *(LinuxWindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event = MouseButtonPressedEvent(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event = MouseButtonReleasedEvent(button);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				LinuxWindowData& data = *(LinuxWindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event = MouseScrolledEvent((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				LinuxWindowData& data = *(LinuxWindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event = MouseMovedEvent((float)xPos, (float)yPos);
				data.EventCallback(event);
			});
	}

	LinuxWindow::~LinuxWindow()
	{
		if (m_Window)
			Close();
	}

	void LinuxWindow::PollEvents()
	{
		if (m_RendererSpecs.API == RenderingAPI::OpenGL && s_Instances > 1)
			glfwMakeContextCurrent(m_Window);

		glfwPollEvents();
	}

	void LinuxWindow::SwapBuffers()
	{
		if (m_RendererSpecs.API == RenderingAPI::OpenGL && m_Window)
			glfwSwapBuffers(m_Window);
	}

	void LinuxWindow::Close()
	{
		// TODO: Renderer

		glfwDestroyWindow(m_Window);
		m_Window = nullptr;
		s_Instances--;

		if (s_Instances == 0)
			glfwTerminate();
	}

	std::pair<float, float> LinuxWindow::GetPosition() const
	{
		int xPos = 0, yPos = 0;
		glfwGetWindowPos(m_Window, &xPos, &yPos);

		return std::pair<float, float>((float)xPos, (float)yPos);
	}

}