#pragma once

#include "CherryTree/Core/Memory.hpp"

#include "CherryTree/Renderer/RendererSpecification.hpp"

#include "CherryTree/Vulkan/VulkanPhysicalDevice.hpp"

#include <vulkan/vulkan.h>

namespace Ct
{

	template<RenderingAPI API>
	class GraphicsContext;

	class VulkanDevice : public RefCounted
	{
	public:
		VulkanDevice(const VkSurfaceKHR surface, Ref<VulkanPhysicalDevice> physicalDevice);
		virtual ~VulkanDevice();

		void Wait() const;

		inline const VkDevice GetVkDevice() const { return m_LogicalDevice; }

		inline const VkQueue GetGraphicsQueue() const { return m_GraphicsQueue; }
		inline const VkQueue GetComputeQueue() const { return m_ComputeQueue; }
		inline const VkQueue GetPresentQueue() const { return m_PresentQueue; }

		inline Ref<VulkanPhysicalDevice> GetPhysicalDevice() const { return m_PhysicalDevice; }

		static Ref<VulkanDevice> Create(const VkSurfaceKHR surface, Ref<VulkanPhysicalDevice> physicalDevice);

	private:
		Ref<VulkanPhysicalDevice> m_PhysicalDevice;
		VkDevice m_LogicalDevice = VK_NULL_HANDLE;

		VkQueue m_GraphicsQueue = VK_NULL_HANDLE;
		VkQueue m_ComputeQueue = VK_NULL_HANDLE;
		VkQueue m_PresentQueue = VK_NULL_HANDLE;
	};

}