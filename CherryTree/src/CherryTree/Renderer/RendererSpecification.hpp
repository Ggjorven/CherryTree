#pragma once

#include <type_traits>
#include <utility>

#include <Pulse/Enum/Enum.hpp>

namespace Ct
{

	enum class RenderingAPI		{ OpenGL, Vulkan };						// Choice of API // TODO: Remove DirectX
	enum class BufferCount		{ Single = 1, Double = 2, Triple = 3};	// Amount of buffers

	struct RendererSpecification
	{
	public:
		const RenderingAPI API;
		BufferCount Buffers;
		bool VSync;

	public:
		constexpr RendererSpecification(const RenderingAPI api = RenderingAPI::Vulkan, BufferCount buffers = BufferCount::Triple, bool vsync = true)
			: API(api), Buffers(buffers), VSync(vsync) {}
		constexpr ~RendererSpecification() = default;
	};

}