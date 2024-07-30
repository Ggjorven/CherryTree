#include "OpenGLApp.hpp"

#include <Pulse/Time/Timer.hpp>
#include <Pulse/Thread/Thread.hpp>

OpenGLApp::OpenGLApp()
{
    WindowSpecification windowSpecs = WindowSpecification(1280, 720, "First Window", [this](Event& e) { this->EventCallback(e); });
    RendererSpecification rendererSpecs = RendererSpecification(BufferCount::Triple, false);

    m_Window = Unique<Window<API>>::Create(windowSpecs, rendererSpecs);
}

void OpenGLApp::Run()
{
    Pulse::Time::Timer timer = {};

    while (m_Window->IsOpen())
    {
        timer.Reset();
        m_Window->PollEvents();

        m_Window->SwapBuffers();
        CT_LOG_TRACE("Deltatime: {0:.4f}ms", timer.ElapsedMillis());
    }
}

void OpenGLApp::EventCallback(Event& e)
{
    EventHandler handler(e);

    handler.Handle<WindowCloseEvent>([this](WindowCloseEvent& e) -> bool
    {
        m_Window->Close();
        return false;
    });
}