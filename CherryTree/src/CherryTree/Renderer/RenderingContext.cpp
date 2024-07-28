#include "ctpch.h"
#include "RenderingContext.hpp"

#include "CherryTree/Core/Logging.hpp"

#include "CherryTree/OpenGL/OpenGLContext.hpp"

namespace Ct
{

	template<>
	Ref<RenderingContextType<RenderingAPI::OpenGL>> Create<RenderingAPI::OpenGL>()
	{
		Log::LogMessage(Log::Level::Trace, "AAAA");
		return Ref<RenderingContextType<RenderingAPI::OpenGL>>::Create();
	}

}