#pragma once

#include <vector>

#include <generic_renderer/core/IPhysicalDevice.h>
#include <generic_renderer/core/IRenderingEnvironment.h>
#include <vulkan_wrapper/core/Instance.h>

#include "core/VulkanPhysicalDevice.h"

namespace vulkan_renderer::core
{
    class VulkanRenderingEnvironment : public generic_renderer::core::IRenderingEnvironment
    {
    public:
        VulkanRenderingEnvironment();
        void release() override;

        const generic_renderer::core::IPhysicalDevice** getAvailablePhysicalDevices() override;
        void test() override;

    private:
        vulkan_wrapper::core::Instance _vulkanInstance;
        std::vector<VulkanPhysicalDevice> _physicalDevices;
        std::vector<const generic_renderer::core::IPhysicalDevice*> _physicalDevicePointers;
    };
}
