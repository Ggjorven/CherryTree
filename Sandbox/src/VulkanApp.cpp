#include "VulkanApp.hpp"

#include <Pulse/Time/Timer.hpp>
#include <Pulse/Thread/Thread.hpp>

VulkanApp::VulkanApp()
{
    WindowSpecification windowSpecs = WindowSpecification(1280, 720, "First Window", [this](Event& e) { this->EventCallback(e); });
    RendererSpecification rendererSpecs = RendererSpecification(BufferCount::Triple, false);

    m_Window = Unique<Window<API>>::Create(windowSpecs, rendererSpecs);
}

void VulkanApp::Run()
{
    Pulse::Time::Timer deltaTimer = {};
    Pulse::Time::Timer intervalTimer = {};
    double interval = 0.300; // Seconds
    uint32_t FPS = 0;

    while (m_Window->IsOpen())
    {
        deltaTimer.Reset();
        m_Window->PollEvents();

        m_Window->SwapBuffers();

        // Update FPS
        FPS++;
        if (intervalTimer.ElapsedSeconds() >= interval)
        {
            CT_LOG_TRACE("Deltatime: {0:.4f}ms | FPS: {1} ({2} / {3:.5f})", deltaTimer.ElapsedMillis(), static_cast<uint32_t>(FPS / intervalTimer.ElapsedSeconds()), FPS, intervalTimer.ElapsedSeconds());
            
            intervalTimer.Reset();
            FPS = 0;
        }
    }
}

void VulkanApp::EventCallback(Event& e)
{
    EventHandler handler(e);

    handler.Handle<WindowCloseEvent>([this](WindowCloseEvent& e) -> bool
    {
        m_Window->Close();
        return false;
    });
}