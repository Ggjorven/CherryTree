#pragma once

#include "CherryTree/Core/Events.hpp"

#include <cstdint>
#include <string>
#include <functional>

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
		~WindowSpecification() = default;
	};

	struct WindowData
	{
	public:
		uint32_t Width = 0, Height = 0;
		std::string Title = {};

		EventCallbackFn EventCallback = nullptr;

		bool Closed = false;

	public:
		inline static uint32_t s_Instances = 0u;
		inline static bool s_GLFWinitialized = false;

	public:
		WindowData() = default;
		WindowData(const WindowSpecification& specs)
			: Width(specs.Width), Height(specs.Height), Title(specs.Title), EventCallback(specs.EventCallback) {}
		~WindowData() = default;
	};

}