#include "OpenGLApp.hpp"
#include "VulkanApp.hpp"

int main(int argc, char* argv[])
{
    {
        OpenGLApp openglApp = {};
        openglApp.Run();
    }
    {
        VulkanApp vulkanApp = {};
        vulkanApp.Run();
    }

    return 0;
}