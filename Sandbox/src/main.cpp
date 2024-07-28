#include "CherryTree/Core/Application.hpp"

#include "CherryTree/Renderer/RenderingContext.hpp"
#include "CherryTree/OpenGL/OpenGLContext.hpp"

int main(int argc, char* argv[])
{
	using namespace Ct;

	Application app;

	auto c = Create<RenderingAPI::OpenGL>();
	c->Init();
	c->Destroy();

	return 0;
}