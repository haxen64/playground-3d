#pragma once

#include <vulkan/vulkan.h>
#include "contexts/InstanceContext.h"

namespace vulkan_renderer::contexts
{
    class PhysicalDeviceContext
    {
    public:
        PhysicalDeviceContext(const InstanceContext* instanceContext, VkPhysicalDevice handle);

        void getPhysicalDeviceFeatures(VkPhysicalDeviceFeatures* pFeatures) const;
        void getPhysicalDeviceProperties(VkPhysicalDeviceProperties* pProperties) const;

    private:
        const InstanceContext* _instanceContext;
        VkPhysicalDevice _handle;

        PFN_vkGetPhysicalDeviceFeatures _vkGetPhysicalDeviceFeatures;
        PFN_vkGetPhysicalDeviceProperties _vkGetPhysicalDeviceProperties;

        void loadFunctions();
    };
}
