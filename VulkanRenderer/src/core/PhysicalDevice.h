#pragma once

#include <vulkan/vulkan.h>

#include "contexts/InstanceContext.h"
#include "contexts/PhysicalDeviceContext.h"
#include "core/PhysicalDeviceType.h"

namespace vulkan_renderer::core
{
    class PhysicalDevice
    {
    public:
        PhysicalDevice(const contexts::InstanceContext* instanceContext, VkPhysicalDevice handle);

        PhysicalDeviceType getType() const;
        const char* getName() const;

    private:
        contexts::PhysicalDeviceContext _context;
        VkPhysicalDeviceProperties _properties;
        VkPhysicalDeviceFeatures _features;
    };
}
