#include "vulkan_wrapper/core/QueueFamilyProperties.h"

namespace vulkan_wrapper::core
{
    QueueFamilyProperties::QueueFamilyProperties(uint32_t id, VkQueueFamilyProperties properties)
        : _id(id), _properties(properties)
    {
    }

    uint32_t QueueFamilyProperties::getId() const
    {
        return _id;
    }

    bool QueueFamilyProperties::supportsGraphics() const
    {
        return _properties.queueFlags & VK_QUEUE_GRAPHICS_BIT;
    }

    bool QueueFamilyProperties::supportsTransfer() const
    {
        return _properties.queueFlags & VK_QUEUE_TRANSFER_BIT;
    }
}
