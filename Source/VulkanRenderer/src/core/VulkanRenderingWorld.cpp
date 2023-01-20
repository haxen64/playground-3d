#include "core/VulkanRenderingWorld.h"

namespace vulkan_renderer::core
{
    VulkanRenderingWorld::VulkanRenderingWorld(vulkan_wrapper::core::Device* device)
        : _device(device)
    {
    }

    generic_renderer::core::IRenderingSurface* VulkanRenderingWorld::createRenderingSurface(HWND hwnd)
    {
        _surfaces.push_back(std::make_unique<VulkanRenderingSurface>(hwnd));
        return _surfaces.back().get();
    }
}
