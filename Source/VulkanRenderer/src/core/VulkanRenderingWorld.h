#pragma once

#include <generic_renderer/core/IRenderingWorld.h>
#include <vulkan_wrapper/core/Device.h>

namespace vulkan_renderer::core
{
    class VulkanRenderingWorld : public generic_renderer::core::IRenderingWorld
    {
    public:
        VulkanRenderingWorld(vulkan_wrapper::core::Device* device);

    private:
        vulkan_wrapper::core::Device* _device;
    };
}
