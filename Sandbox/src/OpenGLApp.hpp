#pragma once

#include <CherryTree/Core/Window.hpp>
#include <CherryTree/Core/Application.hpp>

using namespace Ct;

class OpenGLApp
{
public:
    inline static constinit const RenderingAPI API = RenderingAPI::OpenGL;
public:
    OpenGLApp();
    ~OpenGLApp() = default;

    void Run();

private:
    void EventCallback(Event& e);

private:
    Application m_App = {};

    Unique<Window<API>> m_Window = nullptr;
};
