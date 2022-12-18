#include "Test.h"

#include <iostream>
#include "core/Instance.h"

namespace vulkan_renderer
{
    void test()
    {
        core::Instance instance;
        core::PhysicalDevice gpu = instance.getPhysicalDevice(core::PhysicalDeviceType::DiscreteGpu);
        std::cout << gpu.getName() << std::endl;
    }
}
