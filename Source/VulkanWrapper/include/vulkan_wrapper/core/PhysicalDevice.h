#pragma once

#include "vulkan_wrapper/auxiliary/PhysicalDeviceType.h"
#include "vulkan_wrapper/auxiliary/QueueFamilyProperties.h"
#include "vulkan_wrapper/contexts/InstanceContext.h"

#include <vector>
#include <vulkan/vulkan.h>

namespace vulkan_wrapper::core
{
    class PhysicalDevice
    {
    public:
        PhysicalDevice(const contexts::InstanceContext* context, VkPhysicalDevice handle);

        VkPhysicalDevice getHandle() const;
        auxiliary::PhysicalDeviceType getType() const;
        const char* getName() const;
        std::vector<auxiliary::QueueFamilyProperties> getQueueFamilyProperties() const;

    private:
        const contexts::InstanceContext* _context;
        VkPhysicalDevice _handle;

        VkPhysicalDeviceProperties _properties;
        VkPhysicalDeviceFeatures _features;
    };
}
