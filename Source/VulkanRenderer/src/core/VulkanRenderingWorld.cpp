#include "core/VulkanRenderingWorld.h"

namespace vulkan_renderer::core
{
    VulkanRenderingWorld::VulkanRenderingWorld(vulkan_wrapper::core::Device* device)
        : _device(device)
    {
    }
}
