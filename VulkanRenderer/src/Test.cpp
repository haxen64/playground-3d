#include "Test.h"

#include <algorithm>
#include "core/Instance.h"

namespace vulkan_renderer
{
    void test()
    {
        core::Instance instance;
        auto gpu = instance.getPhysicalDevice(core::PhysicalDeviceType::DiscreteGpu);
        auto queueFamilyProperties = gpu.getQueueFamilyProperties();

        const auto& graphicsQueueFamily = *std::find_if(
            queueFamilyProperties.begin(),
            queueFamilyProperties.end(),
            [](const core::QueueFamilyProperties& properties) { return properties.supportsGraphics(); });

        auto device = instance.createDevice(
            gpu,
            core::DeviceCreationDetails(),
            { std::make_pair(graphicsQueueFamily, core::QueueCreationDetails(1, { 1.0f })) });
    }
}
