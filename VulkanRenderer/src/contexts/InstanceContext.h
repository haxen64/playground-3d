#pragma once

#include <vulkan/vulkan.h>
#include <common/utils/ProcedureRetriever.h>

namespace vulkan_renderer::contexts
{
    class InstanceContext
    {
    public:
        InstanceContext(VkInstance handle, PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr);

        void* getInstanceProcAddr(const char* pName) const;

        VkResult enumeratePhysicalDevices(uint32_t* pPhysicalDeviceCount, VkPhysicalDevice* pPhysicalDevices) const;
        void getPhysicalDeviceFeatures(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures* pFeatures) const;
        void getPhysicalDeviceProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties* pProperties) const;
        void getPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties* pQueueFamilyProperties) const;

    private:
        VkInstance _handle;
        common::utils::ProcedureRetriever _vkInstanceProcedureRetriever;

        PFN_vkEnumeratePhysicalDevices _vkEnumeratePhysicalDevices;
        PFN_vkGetPhysicalDeviceFeatures _vkGetPhysicalDeviceFeatures;
        PFN_vkGetPhysicalDeviceProperties _vkGetPhysicalDeviceProperties;
        PFN_vkGetPhysicalDeviceQueueFamilyProperties _vkGetPhysicalDeviceQueueFamilyProperties;
    };
}
