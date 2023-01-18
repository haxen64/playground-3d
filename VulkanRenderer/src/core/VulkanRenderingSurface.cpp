#include "core/VulkanRenderingSurface.h"

namespace vulkan_renderer::core
{
    VulkanRenderingSurface::VulkanRenderingSurface(vulkan_wrapper::core::Device* device)
        : _device(device)
    {
    }
}
