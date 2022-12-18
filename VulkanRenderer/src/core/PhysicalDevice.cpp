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

    std::vector<QueueFamilyProperties> PhysicalDevice::getQueueFamilyProperties() const
    {
        uint32_t queueFamilyPropertyCount;
        _context.getPhysicalDeviceQueueFamilyProperties(&queueFamilyPropertyCount, nullptr);

        std::vector<VkQueueFamilyProperties> rawQueueFamilyProperties(queueFamilyPropertyCount);
        _context.getPhysicalDeviceQueueFamilyProperties(&queueFamilyPropertyCount, rawQueueFamilyProperties.data());

        std::vector<QueueFamilyProperties> queueFamilyProperties;
        for (uint32_t i = 0; i < rawQueueFamilyProperties.size(); ++i)
            queueFamilyProperties.push_back(QueueFamilyProperties(i, rawQueueFamilyProperties[i]));

        return queueFamilyProperties;
    }
}
