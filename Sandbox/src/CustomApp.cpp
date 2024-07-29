#include "CustomApp.hpp"

#include <Pulse/Thread/Thread.hpp>

CustomApp::CustomApp()
{
    WindowSpecification windowSpecs1 = WindowSpecification(1280, 720, "First Window", [this](Event& e) { this->EventCallback(e); });
    constexpr RendererSpecification rendererSpecs1 = RendererSpecification(RenderingAPI::OpenGL, BufferCount::Triple, false);

    m_Window = Window::Create(windowSpecs1, rendererSpecs1);
}

void CustomApp::Run()
{
    while (m_Window->IsOpen())
    {
        m_Window->PollEvents();

        m_Window->SwapBuffers();
    }
}

void CustomApp::EventCallback(Event& e)
{
    EventHandler handler(e);

    handler.Handle<WindowCloseEvent>([this](WindowCloseEvent& e) -> bool
    {
        m_Window->Close();
        return false;
    });
}