#include "core/PhysicalDevice.h"

namespace vulkan_renderer::core
{
    PhysicalDevice::PhysicalDevice(const contexts::InstanceContext* instanceContext, VkPhysicalDevice handle)
        : _context(contexts::PhysicalDeviceContext(instanceContext, handle))
    {
        _context.getPhysicalDeviceProperties(&_properties);
        _context.getPhysicalDeviceFeatures(&_features);
    }

    PhysicalDeviceType PhysicalDevice::getType() const
    {
        switch (_properties.deviceType)
        {
        case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
            return PhysicalDeviceType::DiscreteGpu;
        default:
            return PhysicalDeviceType::Other;
        }
    }

    const char* PhysicalDevice::getName() const
    {
        return _properties.deviceName;
    }
}
