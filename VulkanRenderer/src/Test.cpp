#include "Test.h"

#include <algorithm>
#include "core/Instance.h"

namespace vulkan_renderer
{
    void test()
    {
        core::Instance instance;
        auto physicalDevices = instance.getPhysicalDevices();

        const auto& discretePhysicalDevice = *std::find_if(
            physicalDevices.begin(),
            physicalDevices.end(),
            [](const core::PhysicalDevice& physicalDevice) { return physicalDevice.getType() == core::PhysicalDeviceType::DiscreteGpu; }
        );

        auto queueFamilyProperties = discretePhysicalDevice.getQueueFamilyProperties();

        const auto& graphicsQueueFamily = *std::find_if(
            queueFamilyProperties.begin(),
            queueFamilyProperties.end(),
            [](const core::QueueFamilyProperties& properties) { return properties.supportsGraphics(); });

        auto device = instance.createDevice(
            discretePhysicalDevice,
            core::DeviceCreationDetails(),
            { std::make_pair(graphicsQueueFamily, core::QueueCreationDetails(1, { 1.0f })) });
    }
}
