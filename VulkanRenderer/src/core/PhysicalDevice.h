#pragma once

#include <vector>
#include <vulkan/vulkan.h>

#include "contexts/InstanceContext.h"
#include "core/PhysicalDeviceType.h"
#include "core/QueueFamilyProperties.h"

namespace vulkan_renderer::core
{
    class PhysicalDevice
    {
    public:
        PhysicalDevice(const contexts::InstanceContext* context, VkPhysicalDevice handle);

        PhysicalDeviceType getType() const;
        const char* getName() const;
        std::vector<QueueFamilyProperties> getQueueFamilyProperties() const;

    private:
        const contexts::InstanceContext* _context;
        VkPhysicalDevice _handle;

        VkPhysicalDeviceProperties _properties;
        VkPhysicalDeviceFeatures _features;
    };
}
