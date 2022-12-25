#pragma once

#include <vector>

#include <vulkan/vulkan.h>

#include "vulkan_wrapper/contexts/InstanceContext.h"
#include "vulkan_wrapper/core/PhysicalDeviceType.h"
#include "vulkan_wrapper/core/QueueFamilyProperties.h"

namespace vulkan_wrapper::core
{
    class PhysicalDevice
    {
    public:
        PhysicalDevice(const contexts::InstanceContext* context, VkPhysicalDevice handle);

        VkPhysicalDevice getHandle() const;
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
