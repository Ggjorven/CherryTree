#pragma once
#if defined(CT_PLATFORM_WINDOWS) || defined(CT_PLATFORM_LINUX)

#include "CherryTree/Core/Memory.hpp"
#include "CherryTree/Core/WindowSpecs.hpp"

#include "CherryTree/Renderer/RendererSpecification.hpp"

#include "CherryTree/Vulkan/VulkanInput.hpp"
#include "CherryTree/Vulkan/VulkanRenderer.hpp"

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

		void Close();
		// Dont' use in any type of EventCallback! + Make sure to not use any window function after this call
		void ForceClose(); 

		inline uint32_t GetWidth() const { return m_WindowData.Width; }
		inline uint32_t GetHeight() const { return m_WindowData.Height; }
		std::pair<float, float> GetPosition() const;

		void SetVSync(bool vsync);
		void SetTitle(const std::string& title);

		inline bool IsVSync() const { return m_Renderer->GetSpecification().VSync; }
		inline bool IsOpen() const { return !m_WindowData.Closed; }

		inline void* GetNativeWindow() { return (void*)m_Window; }

		inline Ref<Renderer<RenderingAPI::Vulkan>> GetRenderer() const { return m_Renderer; }
		inline Ref<Input<RenderingAPI::Vulkan>> GetInput() const { return m_Input; }

	private:
		WindowData m_WindowData;

		GLFWwindow* m_Window = nullptr;

		Ref<Renderer<RenderingAPI::Vulkan>> m_Renderer = nullptr;
		Ref<Input<RenderingAPI::Vulkan>> m_Input = nullptr;
	};

}

#endif