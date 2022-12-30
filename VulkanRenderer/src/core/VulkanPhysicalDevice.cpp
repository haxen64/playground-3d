#include "core/VulkanPhysicalDevice.h"

namespace vulkan_renderer::core
{
    VulkanPhysicalDevice::VulkanPhysicalDevice(const vulkan_wrapper::core::PhysicalDevice* physicalDevice)
        : _physicalDevice(physicalDevice)
    {
    }

    const vulkan_wrapper::core::PhysicalDevice* VulkanPhysicalDevice::getHandle() const
    {
        return _physicalDevice;
    }

    const char* VulkanPhysicalDevice::getName() const
    {
        return _physicalDevice->getName();
    }
}
