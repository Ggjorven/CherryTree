#pragma once
#if defined(CT_PLATFORM_LINUX)

#include "CherryTree/Core/Window.hpp"

#include "CherryTree/Renderer/GraphicsContext.hpp"
#include <GLFW/glfw3.h>

namespace Ct
{

	struct LinuxWindowData
	{
	public:
		uint32_t Width, Height;
		std::string Title;

		EventCallbackFn EventCallback;

		bool Closed = false;

	public:
		LinuxWindowData() = default;
		LinuxWindowData(const WindowSpecification& specs)
			: Width(specs.Width), Height(specs.Height), Title(specs.Title), EventCallback(specs.EventCallback) {}
		~LinuxWindowData() = default;
	};

	class LinuxWindow : public Window
	{
	public:
		LinuxWindow(const WindowSpecification windowSpecs, const RendererSpecification rendererSpecs);
		~LinuxWindow();

		void PollEvents() override;
		void SwapBuffers() override;

		void Close() override;

		inline uint32_t GetWidth() const override { return m_WindowData.Width; }
		inline uint32_t GetHeight() const override { return m_WindowData.Height; }
		std::pair<float, float> GetPosition() const override;

		inline void SetVSync(bool vsync) override { m_RendererSpecs.VSync = vsync; }

		inline bool IsVSync() const override { return m_RendererSpecs.VSync; }
		inline bool IsOpen() const override { return !m_WindowData.Closed; }

		inline void* GetNativeWindow() override { return (void*)m_Window; }

	private:
		LinuxWindowData m_WindowData;
		RendererSpecification m_RendererSpecs;

		GLFWwindow* m_Window = nullptr;

		Unique<GraphicsContext> m_Context = nullptr;
	};

}

#endif