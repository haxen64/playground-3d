#pragma once

#include <vector>
#include <vulkan/vulkan.h>

#include "contexts/InstanceContext.h"
#include "contexts/PhysicalDeviceContext.h"
#include "core/PhysicalDeviceType.h"
#include "core/QueueFamilyProperties.h"

namespace vulkan_renderer::core
{
    class PhysicalDevice
    {
    public:
        PhysicalDevice(const contexts::InstanceContext* instanceContext, VkPhysicalDevice handle);

        PhysicalDeviceType getType() const;
        const char* getName() const;
        std::vector<QueueFamilyProperties> getQueueFamilyProperties() const;

    private:
        contexts::PhysicalDeviceContext _context;
        VkPhysicalDeviceProperties _properties;
        VkPhysicalDeviceFeatures _features;
    };
}
