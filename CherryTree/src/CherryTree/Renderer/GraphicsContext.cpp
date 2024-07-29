#include "ctpch.h"
#include "GraphicsContext.hpp"

#include "CherryTree/Core/Logging.hpp"

#include "CherryTree/OpenGL/OpenGLContext.hpp"

namespace Ct
{

	Unique<GraphicsContext> GraphicsContext::Create(const RenderingAPI api, void* window)
	{
		switch (api)
		{
		case RenderingAPI::OpenGL:
			return Unique<OpenGLContext>::Create(window);
		case RenderingAPI::Vulkan:

		default:
			CT_ASSERT(false, "Invalid RenderingAPI selected.");
			break;
		}

		return nullptr;
	}

}