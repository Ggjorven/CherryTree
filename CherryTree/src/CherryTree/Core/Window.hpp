#pragma once

#include "CherryTree/Core/Memory.hpp"
#include "CherryTree/Core/Events.hpp"

#include "CherryTree/Renderer/RendererSpecification.hpp"

#include <cstdint>
#include <string>
#include <utility>

namespace Ct
{

	typedef std::function<void(Event&)> EventCallbackFn;

	struct WindowSpecification
	{
	public:
		uint32_t Width, Height;
		std::string Title;

		EventCallbackFn EventCallback;

	public:
		WindowSpecification(uint32_t width = 1280, uint32_t height = 720, const std::string& title = "CherryTree Window", EventCallbackFn eventCallback = nullptr)
			: Width(width), Height(height), Title(title), EventCallback(eventCallback) {}
		constexpr ~WindowSpecification() = default;
	};

	class Window // Window closes on destructor.
	{
	public:
		Window() = default;
		virtual ~Window() = default;

		virtual void PollEvents() = 0;
		virtual void SwapBuffers() = 0;

		virtual void Close() = 0; // Make sure to not use any window function after this call

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual std::pair<float, float> GetPosition() const = 0;

		virtual void SetVSync(bool vsync) = 0;

		virtual bool IsVSync() const = 0;
		virtual bool IsOpen() const = 0;

		virtual void* GetNativeWindow() = 0;

		static Unique<Window> Create(const WindowSpecification windowSpecs, const RendererSpecification rendererSpecs);
	};

}