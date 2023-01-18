#pragma once

#include <generic_renderer/core/IRenderingSurface.h>
#include <vulkan_wrapper/core/Device.h>

namespace vulkan_renderer::core
{
    class VulkanRenderingSurface : public generic_renderer::core::IRenderingSurface
    {
    public:
        VulkanRenderingSurface(vulkan_wrapper::core::Device* device);

    private:
        vulkan_wrapper::core::Device* _device;
    };
}
