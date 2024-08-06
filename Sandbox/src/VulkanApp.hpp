#pragma once

#include <CherryTree/Core/Window.hpp>
#include <CherryTree/Core/Application.hpp>

using namespace Ct;

class VulkanApp
{
public:
    inline static constinit const RenderingAPI API = RenderingAPI::Vulkan;
public:
    VulkanApp();
    ~VulkanApp() = default;

    void Run();

private:
    void EventCallback(Event& e);

private:
    Application m_App = {};

    Unique<Window<API>> m_Window = nullptr;
};
