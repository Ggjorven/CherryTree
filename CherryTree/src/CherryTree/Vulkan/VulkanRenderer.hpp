#pragma once

#include "CherryTree/Core/Memory.hpp"

#include "CherryTree/Renderer/RendererSpecification.hpp"

#include "CherryTree/Vulkan/VulkanAllocator.hpp"
#include "CherryTree/Vulkan/VulkanSwapChain.hpp"

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

		void Init(uint32_t width, uint32_t height);

		void Present();

		inline const RendererSpecification& GetSpecification() const { return m_Specification; }
		inline Ref<Allocator<RenderingAPI::Vulkan>> GetAllocator() const { return m_Allocator; }

	private:
		void* m_Window;
		RendererSpecification m_Specification;

		Ref<Allocator<RenderingAPI::Vulkan>> m_Allocator = nullptr;

		VkSurfaceKHR m_Surface = VK_NULL_HANDLE;
		Ref<VulkanSwapChain> m_SwapChain = nullptr;
	};

}