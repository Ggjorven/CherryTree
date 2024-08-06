#include "ctpch.h"
#include "VulkanImage.hpp"

#include "CherryTree/Core/Logging.hpp"

#include "CherryTree/Vulkan/VulkanContext.hpp"
#include "CherryTree/Vulkan/VulkanAllocator.hpp"

namespace Ct
{

	///////////////////////////////////////////////////////////
	// Specifications
	///////////////////////////////////////////////////////////
	ImageSpecification::ImageSpecification(uint32_t width, uint32_t height, ImageUsageFlags flags)
		: Usage(ImageUsage::Size), Width(width), Height(height), Flags(flags)
	{
	}

	ImageSpecification::ImageSpecification(const std::filesystem::path& path, ImageUsageFlags flags)
		: Usage(ImageUsage::File), Path(path), Flags(flags)
	{
	}

	///////////////////////////////////////////////////////////
	// Core class
	///////////////////////////////////////////////////////////
	Image<RenderingAPI::Vulkan>::Image(const ImageSpecification& specs)
		: m_Specification(specs)
	{
	}

	Image<RenderingAPI::Vulkan>::~Image()
	{
	}

	void Image<RenderingAPI::Vulkan>::SetData(void* data, size_t size)
	{
	}

	void Image<RenderingAPI::Vulkan>::Resize(uint32_t width, uint32_t height)
	{
	}

	void Image<RenderingAPI::Vulkan>::Transition(ImageLayout initial, ImageLayout final)
	{
	}

}