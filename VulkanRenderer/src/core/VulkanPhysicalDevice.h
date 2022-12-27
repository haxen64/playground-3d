#pragma once

#include <generic_renderer/core/IPhysicalDevice.h>
#include <vulkan_wrapper/core/PhysicalDevice.h>

namespace vulkan_renderer::core
{
    class VulkanPhysicalDevice : public generic_renderer::core::IPhysicalDevice
    {
    public:
        VulkanPhysicalDevice(const vulkan_wrapper::core::PhysicalDevice* physicalDevice);

        const char* getName() const override;

    private:
        const vulkan_wrapper::core::PhysicalDevice* _physicalDevice;
    };
}
