#include "ctpch.h"
#include "OpenGLWindow.hpp"
#if defined (CT_PLATFORM_WINDOWS) || defined(CT_PLATFORM_LINUX)

#include "CherryTree/Core/Logging.hpp"

#include "CherryTree/OpenGL/OpenGLContext.hpp"

#include <glad/glad.h>

namespace Ct
{

	static void GLFWErrorCallBack(int errorCode, const char* description)
	{
		CT_LOG_ERROR("[GLFW]: ({0}), {1}", errorCode, description);
	}



	Window<RenderingAPI::OpenGL>::Window(const WindowSpecification windowSpecs, const RendererSpecification rendererSpecs)
		: m_WindowData(windowSpecs)
	{
		CT_ASSERT(m_WindowData.EventCallback, "No event callback was passed in.");

		if (!WindowData::s_GLFWinitialized)
		{
			int succes = glfwInit();
			if (!succes)
				CT_LOG_ERROR("(GLFW) glfwInit() failed");

			WindowData::s_GLFWinitialized = true;
			glfwSetErrorCallback(GLFWErrorCallBack);
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, (int)GraphicsContext<RenderingAPI::OpenGL>::Version.first);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, (int)GraphicsContext<RenderingAPI::OpenGL>::Version.second);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		m_Window = glfwCreateWindow((int)windowSpecs.Width, (int)windowSpecs.Height, windowSpecs.Title.c_str(), nullptr, nullptr);
		CT_ASSERT(m_Window, "Failed to create window...");
		WindowData::s_Instances++;

		glfwMakeContextCurrent(m_Window);

		using Context = GraphicsContext<RenderingAPI::OpenGL>;

		if (Context::IncUsers() == 1)
			GraphicsContext<RenderingAPI::OpenGL>::Init();

		m_Input = Ref<Ct::Input<RenderingAPI::OpenGL>>::Create((void*)m_Window);

		glfwSetWindowUserPointer(m_Window, (void*)&m_WindowData); //So we can access/get to the data in lambda functions
		
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
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
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Closed = true;

			WindowCloseEvent event = WindowCloseEvent();
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

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
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event = KeyTypedEvent(keycode);
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

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
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event = MouseScrolledEvent((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event = MouseMovedEvent((float)xPos, (float)yPos);
			data.EventCallback(event);
		});

		m_Renderer = Ref<Ct::Renderer<RenderingAPI::OpenGL>>::Create((void*)m_Window, rendererSpecs);

		CT_LOG_INFO("Succesfully created OpenGL window. OpenGL version: {0}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
	}

	Window<RenderingAPI::OpenGL>::~Window()
	{
		if (m_Window)
			ForceClose();
	}

	void Window<RenderingAPI::OpenGL>::PollEvents()
	{
		if (WindowData::s_Instances > 1)
			glfwMakeContextCurrent(m_Window);

		glfwPollEvents();
	}

	void Window<RenderingAPI::OpenGL>::SwapBuffers()
	{
		if (m_Window)
			glfwSwapBuffers(m_Window);
	}

	void Window<RenderingAPI::OpenGL>::Close()
	{
		m_WindowData.Closed = true;
	}

	void Window<RenderingAPI::OpenGL>::ForceClose()
	{
		m_WindowData.Closed = true;

		if (GraphicsContext<RenderingAPI::OpenGL>::DecUsers() == 0)
			GraphicsContext<RenderingAPI::OpenGL>::Destroy();

		// TODO: Renderer

		glfwDestroyWindow(m_Window);
		m_Window = nullptr;
		WindowData::s_Instances--;

		if (WindowData::s_Instances == 0)
		{
			glfwTerminate();
			WindowData::s_GLFWinitialized = false;
		}
	}

	void Window<RenderingAPI::OpenGL>::SetVSync(bool vsync)
	{
		// TODO: Renderer
	}

	void Window<RenderingAPI::OpenGL>::SetTitle(const std::string& title)
	{
		m_WindowData.Title = title;
		glfwSetWindowTitle(m_Window, m_WindowData.Title.c_str());
	}

	std::pair<float, float> Window<RenderingAPI::OpenGL>::GetPosition() const
	{
		int xPos = 0, yPos = 0;
		glfwGetWindowPos(m_Window, &xPos, &yPos);

		return std::pair<float, float>((float)xPos, (float)yPos);
	}

}

#endif