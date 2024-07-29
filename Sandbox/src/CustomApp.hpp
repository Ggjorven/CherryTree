#pragma once

#include <CherryTree/Core/Application.hpp>

#include <CherryTree/Core/Window.hpp>

using namespace Ct;

class CustomApp
{
public:
    CustomApp();
    ~CustomApp() = default;

    void Run();

private:
    void EventCallback(Event& e);

private:
    Application m_App = {};

    Unique<Window> m_Window = nullptr;
};
