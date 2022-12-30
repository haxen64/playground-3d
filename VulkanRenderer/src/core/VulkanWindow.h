#pragma once

#include <generic_renderer/core/IWindow.h>
#include <vulkan_wrapper/core/Device.h>

namespace vulkan_renderer::core
{
    class VulkanWindow : public generic_renderer::core::IWindow
    {
    public:
        VulkanWindow(vulkan_wrapper::core::Device* device);

    private:
        vulkan_wrapper::core::Device* _device;
    };
}
