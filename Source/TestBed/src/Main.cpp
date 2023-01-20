#include <common/helpers/Interoperability.h>
#include <generic_renderer/core/IRenderingEnvironment.h>

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <iostream>
#include <stdexcept>

int main()
{
    try
    {
        if (!glfwInit())
            throw std::runtime_error("Failed to init GLFW.");

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        GLFWwindow* window = glfwCreateWindow(1280, 720, "TestBed", nullptr, nullptr);
        if (window == nullptr)
            throw std::runtime_error("Failed to create a GLFW window.");

        auto vulkanRendererLibHandle = common::helpers::Interoperability::LoadWindowsLibrary("vulkan_renderer.dll");
        auto createRenderingEnvironment = (generic_renderer::core::IRenderingEnvironment * (*)())GetProcAddress(vulkanRendererLibHandle.value(), "createRenderingEnvironment");
        auto renderingEnvironment = createRenderingEnvironment();
        auto physicalDevice = *renderingEnvironment->getAvailablePhysicalDevices();
        auto renderingWorld = renderingEnvironment->createRenderingWorld(physicalDevice);
        auto renderingSurface = renderingWorld->createRenderingSurface(glfwGetWin32Window(window));
        renderingEnvironment->release();

        while (!glfwWindowShouldClose(window))
        {
            glfwWaitEvents();
        }

        glfwTerminate();
    }
    catch (const std::exception& ex)
    {
        std::cout << "An unhandled exception has occurred:" << std::endl;
        std::cout << "\t" << ex.what() << std::endl;
        return -1;
    }
    catch (...)
    {
        std::cout << "An unhandled unknown exception has occurred." << std::endl;
        return -2;
    }

    return 0;
}
