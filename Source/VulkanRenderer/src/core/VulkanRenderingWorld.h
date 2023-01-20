#pragma once

#include "core/VulkanRenderingSurface.h"

#include <generic_renderer/core/IRenderingSurface.h>
#include <generic_renderer/core/IRenderingWorld.h>
#include <vulkan_wrapper/core/Device.h>

#include <memory>
#include <vector>
#include <windows.h>

namespace vulkan_renderer::core
{
    class VulkanRenderingWorld : public generic_renderer::core::IRenderingWorld
    {
    public:
        VulkanRenderingWorld(vulkan_wrapper::core::Device* device);

        generic_renderer::core::IRenderingSurface* createRenderingSurface(HWND hwnd) override;

    private:
        vulkan_wrapper::core::Device* _device;
        std::vector<std::unique_ptr<VulkanRenderingSurface>> _surfaces;
    };
}
