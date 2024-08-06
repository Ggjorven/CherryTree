#pragma once

#include <type_traits>
#include <utility>

#include <Pulse/Enum/Enum.hpp>

#include "CherryTree/Core/Logging.hpp"

namespace Ct
{

	enum class RenderingAPI : uint8_t		{ None = 0, OpenGL, Vulkan };			// Choice of API 
	enum class BufferCount : uint8_t		{ Single = 1, Double = 2, Triple = 3};	// Amount of buffers
	
	struct RendererSpecification
	{
	public:
		BufferCount Buffers;
		bool VSync;

	public:
		RendererSpecification(BufferCount buffers = BufferCount::Triple, bool vsync = true)
			: Buffers(buffers), VSync(vsync) 
		{
		}
		~RendererSpecification() = default;
	};

}