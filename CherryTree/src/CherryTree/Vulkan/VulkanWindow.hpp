#pragma once

#include "CherryTree/Core/Memory.hpp"
#include "CherryTree/Core/WindowSpecs.hpp"

#include "CherryTree/Renderer/GraphicsContext.hpp"
#include "CherryTree/Renderer/RendererSpecification.hpp"

#include <GLFW/glfw3.h>

namespace Ct
{

	template<RenderingAPI API>
	class Window;

	template<>
	class Window<RenderingAPI::Vulkan>
	{
	public:
		Window(const WindowSpecification windowSpecs, const RendererSpecification rendererSpecs);
		virtual ~Window();

		void PollEvents();
		void SwapBuffers();

		void Close(); // Make sure to not use any window function after this call

		inline uint32_t GetWidth() const { return m_WindowData.Width; }
		inline uint32_t GetHeight() const { return m_WindowData.Height; }
		std::pair<float, float> GetPosition() const;

		void SetVSync(bool vsync);
		void SetTitle(const std::string& title);

		inline bool IsVSync() const { return m_RendererSpecs.VSync; }
		inline bool IsOpen() const { return !m_WindowData.Closed; }

		inline void* GetNativeWindow() { return (void*)m_Window; }

	private:
		WindowData m_WindowData;
		RendererSpecification m_RendererSpecs; // TODO: Move to renderer

		GLFWwindow* m_Window = nullptr;

		Unique<GraphicsContext<RenderingAPI::Vulkan>> m_Context = nullptr;
	};

}