#pragma once

#include "CherryTree/Renderer/GraphicsContext.hpp"

#include <cstdint>
#include <utility>

namespace Ct
{

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(void* window);
		~OpenGLContext();

    public:
		inline static constinit const std::pair<uint8_t, uint8_t> Version = { 4, 5 };
	};

}