#pragma once

#include <vulkan/vulkan.h>
#include "utils/ProcedureRetriever.h"

namespace vulkan_renderer::contexts
{
    class InstanceContext
    {
    public:
        InstanceContext();

        InstanceContext(const InstanceContext&) = delete;
        InstanceContext(InstanceContext&&) = delete;
        InstanceContext& operator=(const InstanceContext&) = delete;
        InstanceContext& operator=(InstanceContext&&) = delete;

        PFN_vkGetPhysicalDeviceFeatures getPhysicalDeviceFeatures;
        PFN_vkGetPhysicalDeviceProperties getPhysicalDeviceProperties;

        VkResult enumeratePhysicalDevices(uint32_t* pPhysicalDeviceCount, VkPhysicalDevice* pPhysicalDevices) const;

    private:
        VkInstance _handle;
        utils::ProcedureRetriever _vkProcedureRetriever;
        utils::ProcedureRetriever _vkInstanceProcedureRetriever;

        PFN_vkEnumeratePhysicalDevices _vkEnumeratePhysicalDevices;

        void loadFunctions();
    };
}
