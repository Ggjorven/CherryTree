#include "ctpch.h"
#include "Application.hpp"

#include "CherryTree/Core/Logging.hpp"

namespace Ct
{

	Application::Application()
	{
		Log::Init();
	}

	Application::~Application()
	{
	}

}