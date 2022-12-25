#include "vulkan_renderer/Test.h"

#include <algorithm>
#include <vulkan_wrapper/core/Instance.h>

namespace vulkan_renderer
{
    void test()
    {
        vulkan_wrapper::core::Instance instance;
        auto physicalDevices = instance.getPhysicalDevices();

        const auto& discretePhysicalDevice = *std::find_if(
            physicalDevices.begin(),
            physicalDevices.end(),
            [](const vulkan_wrapper::core::PhysicalDevice& physicalDevice) { return physicalDevice.getType() == vulkan_wrapper::core::PhysicalDeviceType::DiscreteGpu; }
        );

        auto queueFamilyProperties = discretePhysicalDevice.getQueueFamilyProperties();

        const auto& graphicsQueueFamily = *std::find_if(
            queueFamilyProperties.begin(),
            queueFamilyProperties.end(),
            [](const vulkan_wrapper::core::QueueFamilyProperties& properties) { return properties.supportsGraphics(); });

        auto device = instance.createDevice(
            discretePhysicalDevice,
            vulkan_wrapper::core::DeviceCreationDetails(),
            { std::make_pair(graphicsQueueFamily, vulkan_wrapper::core::QueueCreationDetails(1, { 1.0f })) });

        auto graphicsQueue = device->getQueues(graphicsQueueFamily).front();
    }
}
