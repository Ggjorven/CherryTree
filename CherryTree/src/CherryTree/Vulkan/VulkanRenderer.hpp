#pragma once

#include "CherryTree/Core/Memory.hpp"

#include "CherryTree/Renderer/RendererSpecification.hpp"

#include <vulkan/vulkan.h>

#include <cstdint>
#include <utility>

namespace Ct
{

	template<RenderingAPI API>
	class Renderer;

	template<>
	class Renderer<RenderingAPI::Vulkan> : public RefCounted
	{
	public:
		Renderer(void* window, const RendererSpecification& specs, const VkSurfaceKHR surface);
		~Renderer();

		void Init();

		void Present();

		inline const RendererSpecification& GetSpecification() const { return m_Specification; }

	private:
		void* m_Window;
		RendererSpecification m_Specification;

		VkSurfaceKHR m_Surface = VK_NULL_HANDLE;
		//Ref<VulkanSwapChain> m_SwapChain = nullptr;
	};

}