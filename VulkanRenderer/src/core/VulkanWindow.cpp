#include "core/VulkanWindow.h"

namespace vulkan_renderer::core
{
    VulkanWindow::VulkanWindow(vulkan_wrapper::core::Device* device)
        : _device(device)
    {
    }
}
