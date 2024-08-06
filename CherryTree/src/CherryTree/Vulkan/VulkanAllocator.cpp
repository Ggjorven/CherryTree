#include "ctpch.h"
#include "VulkanAllocator.hpp"

#include "CherryTree/Core/Logging.hpp"

#include "CherryTree/Vulkan/VulkanUtils.hpp"
#include "CherryTree/Vulkan/VulkanContext.hpp"

///////////////////////////////////////////////////////////
// Helper functions
///////////////////////////////////////////////////////////
static void* VKAPI_PTR VmaAllocFn(void* pUserData, size_t size, size_t alignment, VkSystemAllocationScope allocationScope)
{
	//s_Allocations++;
	//APP_LOG_TRACE("Allocated Vulkan Memory: (Size: {0} | Total Allocs: {1})", size, s_Allocations);

	return std::malloc(size);
}

static void VKAPI_PTR VmaFreeFn(void* pUserData, void* pMemory)
{
	//s_Allocations--;
	//APP_LOG_TRACE("Freed Vulkan Memory: (Total Allocs: {0})", s_Allocations);

	std::free(pMemory);
}

static void* VKAPI_PTR VmaReallocFn(void* pUserData, void* pOriginal, size_t size, size_t alignment, VkSystemAllocationScope allocationScope)
{
	return std::realloc(pOriginal, size);
}

namespace Ct
{

	static VmaAllocator s_Allocator = VK_NULL_HANDLE;

	///////////////////////////////////////////////////////////
	// Core functionality
	///////////////////////////////////////////////////////////
	void Allocator<RenderingAPI::Vulkan>::Init()
	{
		using Context = GraphicsContext<RenderingAPI::Vulkan>;

		VkAllocationCallbacks callbacks = {};
		callbacks.pUserData = nullptr;
		callbacks.pfnAllocation = VmaAllocFn;
		callbacks.pfnFree = VmaFreeFn;
		callbacks.pfnReallocation = VmaReallocFn;
		callbacks.pfnInternalAllocation = nullptr;
		callbacks.pfnInternalFree = nullptr;

		VmaAllocatorCreateInfo allocatorInfo = {};
		allocatorInfo.instance = Context::GetVkInstance();
		allocatorInfo.physicalDevice = Context::GetPhysicalDevice()->GetVkPhysicalDevice();
		allocatorInfo.device = Context::GetDevice()->GetVkDevice();
		allocatorInfo.pAllocationCallbacks = &callbacks;

		VK_CHECK_RESULT(vmaCreateAllocator(&allocatorInfo, &s_Allocator));
	}

	void Allocator<RenderingAPI::Vulkan>::Destroy()
	{
		if (s_Allocator)
		{
			vmaDestroyAllocator(s_Allocator);
			s_Allocator = VK_NULL_HANDLE;
		}
	}



	Allocator<RenderingAPI::Vulkan>::Allocator(const uint8_t framesInFlight)
		: m_FramesInFlight(framesInFlight)
	{
	}

	Allocator<RenderingAPI::Vulkan>::~Allocator()
	{
	}

	Ref<Image<RenderingAPI::Vulkan>> Allocator<RenderingAPI::Vulkan>::AllocImage(const ImageSpecification& specs)
	{
		return Ref<Image<RenderingAPI::Vulkan>>(new Image<RenderingAPI::Vulkan>(specs));
	}

	Ref<CommandBuffer<RenderingAPI::Vulkan>> Allocator<RenderingAPI::Vulkan>::AllocCmdBuf()
	{
		return Ref<CommandBuffer<RenderingAPI::Vulkan>>(new CommandBuffer<RenderingAPI::Vulkan>(m_FramesInFlight, m_CommandPool));
	}

}
