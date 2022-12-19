#include "Test.h"

#include "core/Instance.h"

namespace vulkan_renderer
{
    void test()
    {
        core::Instance instance;
        auto gpu = instance.getPhysicalDevice(core::PhysicalDeviceType::DiscreteGpu);
        auto queueFamilyProperties = gpu.getQueueFamilyProperties();
        auto device = instance.createDevice(gpu);
    }
}
