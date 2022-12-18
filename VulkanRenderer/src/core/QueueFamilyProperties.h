#pragma once

#include <vulkan/vulkan.h>

namespace vulkan_renderer::core
{
    class QueueFamilyProperties
    {
    public:
        QueueFamilyProperties(uint32_t id, VkQueueFamilyProperties properties);

        uint32_t getId() const;
        bool supportsGraphics() const;
        bool supportsTransfer() const;

    private:
        uint32_t _id;
        VkQueueFamilyProperties _properties;
    };
}
