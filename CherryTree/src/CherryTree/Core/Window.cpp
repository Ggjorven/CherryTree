#include "ctpch.h"
#include "Window.hpp"

#include "CherryTree/Core/Logging.hpp"

#include "CherryTree/Platforms/Windows/WindowsWindow.hpp"
#include "CherryTree/Platforms/Linux/LinuxWindow.hpp"

namespace Ct
{

	Unique<Window> Window::Create(const WindowSpecification windowSpecs, const RendererSpecification rendererSpecs)
	{
		#if defined(CT_PLATFORM_WINDOWS)
			return Unique<WindowsWindow>::Create(windowSpecs, rendererSpecs);
		#elif defined(CT_PLATFORM_LINUX)
			return Unique<LinuxWindow>::Create(windowSpecs, rendererSpecs);
		#else
			#error CherryTree: Platform not supported.
		#endif

		return nullptr;
	}

}