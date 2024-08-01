#pragma once
#if defined (CT_PLATFORM_WINDOWS) || defined(CT_PLATFORM_LINUX)

#include "CherryTree/Core/Memory.hpp"
#include "CherryTree/Core/WindowSpecs.hpp"

#include "CherryTree/Renderer/GraphicsContext.hpp"
#include "CherryTree/Renderer/RendererSpecification.hpp"

#include "CherryTree/OpenGL/OpenGLInput.hpp"
#include "CherryTree/OpenGL/OpenGLRenderer.hpp"

#include <GLFW/glfw3.h>

namespace Ct
{

	template<RenderingAPI API>
	class Window;

	template<>
	class Window<RenderingAPI::OpenGL>
	{
	public:
		Window(const WindowSpecification windowSpecs, const RendererSpecification rendererSpecs);
		virtual ~Window();

		void PollEvents();
		void SwapBuffers();

		void Close();
		// Dont' use in any type of EventCallback! + Make sure to not use any window function after this call
		void ForceClose(); 

		inline uint32_t GetWidth() const { return m_WindowData.Width; }
		inline uint32_t GetHeight() const { return m_WindowData.Height; }
		std::pair<float, float> GetPosition() const;

		void SetVSync(bool vsync);
		void SetTitle(const std::string& title);

		inline bool IsVSync() const { return m_Context->GetSpecification().VSync; }
		inline bool IsOpen() const { return !m_WindowData.Closed; }

		inline void* GetNativeWindow() { return (void*)m_Window; }

		inline Ref<Renderer<RenderingAPI::OpenGL>> GetRenderer() const { return m_Renderer; }
		inline Ref<Input<RenderingAPI::OpenGL>> GetInput() const { return m_Input; }

	private:
		WindowData m_WindowData;

		GLFWwindow* m_Window = nullptr;

		Ref<GraphicsContext<RenderingAPI::OpenGL>> m_Context = nullptr;
		Ref<Renderer<RenderingAPI::OpenGL>> m_Renderer = nullptr;
		Ref<Input<RenderingAPI::OpenGL>> m_Input = nullptr;
	};

}

#endif