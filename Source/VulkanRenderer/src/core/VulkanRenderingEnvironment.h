#pragma once

#include <memory>
#include <vector>

#include <generic_renderer/core/IPhysicalDevice.h>
#include <generic_renderer/core/IRenderingEnvironment.h>
#include <generic_renderer/core/IRenderingWorld.h>
#include <vulkan_wrapper/core/Instance.h>

#include "core/VulkanPhysicalDevice.h"
#include "core/VulkanRenderingWorld.h"

namespace vulkan_renderer::core
{
    class VulkanRenderingEnvironment : public generic_renderer::core::IRenderingEnvironment
    {
    public:
        VulkanRenderingEnvironment();
        void release() override;

        const generic_renderer::core::IPhysicalDevice** getAvailablePhysicalDevices() override;
        generic_renderer::core::IRenderingWorld* createRenderingWorld(const generic_renderer::core::IPhysicalDevice* physicalDevice) override;

    private:
        vulkan_wrapper::core::Instance _vulkanInstance;
        std::vector<std::unique_ptr<VulkanPhysicalDevice>> _physicalDevices;
        std::vector<const generic_renderer::core::IPhysicalDevice*> _physicalDevicePointers;
        std::vector<std::unique_ptr<VulkanRenderingWorld>> _worlds;
    };
}
