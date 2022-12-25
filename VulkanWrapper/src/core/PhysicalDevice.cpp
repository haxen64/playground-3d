#include "vulkan_wrapper/core/PhysicalDevice.h"

namespace vulkan_wrapper::core
{
    PhysicalDevice::PhysicalDevice(const contexts::InstanceContext* context, VkPhysicalDevice handle)
        : _context(context), _handle(handle)
    {
        _context->getPhysicalDeviceProperties(_handle, &_properties);
        _context->getPhysicalDeviceFeatures(_handle, &_features);
    }

    VkPhysicalDevice PhysicalDevice::getHandle() const
    {
        return _handle;
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
        _context->getPhysicalDeviceQueueFamilyProperties(_handle, &queueFamilyPropertyCount, nullptr);

        std::vector<VkQueueFamilyProperties> rawQueueFamilyProperties(queueFamilyPropertyCount);
        _context->getPhysicalDeviceQueueFamilyProperties(_handle, &queueFamilyPropertyCount, rawQueueFamilyProperties.data());

        std::vector<QueueFamilyProperties> queueFamilyProperties;
        for (uint32_t i = 0; i < rawQueueFamilyProperties.size(); ++i)
            queueFamilyProperties.push_back(QueueFamilyProperties(i, rawQueueFamilyProperties[i]));

        return queueFamilyProperties;
    }
}
