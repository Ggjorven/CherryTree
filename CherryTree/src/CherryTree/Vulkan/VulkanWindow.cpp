#include "ctpch.h"
#include "VulkanWindow.hpp"
#if defined(CT_PLATFORM_WINDOWS) || defined(CT_PLATFORM_LINUX)

#include "CherryTree/Core/Logging.hpp"

namespace Ct
{

	static void GLFWErrorCallBack(int errorCode, const char* description)
	{
		CT_LOG_ERROR("[GLFW]: ({0}), {1}", errorCode, description);
	}



	Window<RenderingAPI::Vulkan>::Window(const WindowSpecification windowSpecs, const RendererSpecification rendererSpecs)
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

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		m_Window = glfwCreateWindow((int)windowSpecs.Width, (int)windowSpecs.Height, windowSpecs.Title.c_str(), nullptr, nullptr);
		CT_ASSERT(m_Window, "Failed to create window...");
		WindowData::s_Instances++;

		m_Context = Ref<GraphicsContext<RenderingAPI::Vulkan>>::Create((void*)m_Window, rendererSpecs);

		Input = Ref<Ct::Input<RenderingAPI::Vulkan>>::Create((void*)m_Window);

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

		CT_LOG_INFO("Succesfully created Vulkan window. Vulkan version: {0}.{1}.XXX", GraphicsContext<RenderingAPI::Vulkan>::Version.first, GraphicsContext<RenderingAPI::Vulkan>::Version.second);

		Renderer = Ref<Ct::Renderer<RenderingAPI::Vulkan>>::Create(m_Context);
	}

	Window<RenderingAPI::Vulkan>::~Window()
	{
		if (m_Window)
			ForceClose();
	}

	void Window<RenderingAPI::Vulkan>::PollEvents()
	{
		glfwPollEvents();
	}

	void Window<RenderingAPI::Vulkan>::SwapBuffers()
	{
		Renderer->Present();
	}

	void Window<RenderingAPI::Vulkan>::Close()
	{
		m_WindowData.Closed = true;
	}

	void Window<RenderingAPI::Vulkan>::ForceClose()
	{
		m_WindowData.Closed = true;

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

	void Window<RenderingAPI::Vulkan>::SetVSync(bool vsync)
	{
		// TODO: Renderer
	}

	void Window<RenderingAPI::Vulkan>::SetTitle(const std::string& title)
	{
		m_WindowData.Title = title;
		glfwSetWindowTitle(m_Window, m_WindowData.Title.c_str());
	}

	std::pair<float, float> Window<RenderingAPI::Vulkan>::GetPosition() const
	{
		int xPos = 0, yPos = 0;
		glfwGetWindowPos(m_Window, &xPos, &yPos);

		return std::pair<float, float>((float)xPos, (float)yPos);
	}

}

#endif