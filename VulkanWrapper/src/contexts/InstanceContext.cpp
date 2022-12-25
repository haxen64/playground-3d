#include "vulkan_wrapper/contexts/InstanceContext.h"

namespace vulkan_wrapper::contexts
{
    InstanceContext::InstanceContext(VkInstance handle, PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr)
        : _handle(handle)
    {
        _vkInstanceProcedureRetriever = common::utils::ProcedureRetriever([=](const char* procedureName) { return vkGetInstanceProcAddr(handle, procedureName); });

        _vkCreateDevice = (PFN_vkCreateDevice)getInstanceProcAddr("vkCreateDevice");
        _vkDestroyDevice = (PFN_vkDestroyDevice)getInstanceProcAddr("vkDestroyDevice");
        _vkEnumeratePhysicalDevices = (PFN_vkEnumeratePhysicalDevices)getInstanceProcAddr("vkEnumeratePhysicalDevices");
        _vkGetPhysicalDeviceFeatures = (PFN_vkGetPhysicalDeviceFeatures)getInstanceProcAddr("vkGetPhysicalDeviceFeatures");
        _vkGetPhysicalDeviceProperties = (PFN_vkGetPhysicalDeviceProperties)getInstanceProcAddr("vkGetPhysicalDeviceProperties");
        _vkGetPhysicalDeviceQueueFamilyProperties = (PFN_vkGetPhysicalDeviceQueueFamilyProperties)getInstanceProcAddr("vkGetPhysicalDeviceQueueFamilyProperties");
    }

    void* InstanceContext::getInstanceProcAddr(const char* pName) const
    {
        return _vkInstanceProcedureRetriever.getProcedureAddress(pName);
    }

    VkResult InstanceContext::createDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDevice* pDevice) const
    {
        return _vkCreateDevice(physicalDevice, pCreateInfo, pAllocator, pDevice);
    }

    void InstanceContext::destroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator) const
    {
        _vkDestroyDevice(device, pAllocator);
    }

    VkResult InstanceContext::enumeratePhysicalDevices(uint32_t* pPhysicalDeviceCount, VkPhysicalDevice* pPhysicalDevices) const
    {
        return _vkEnumeratePhysicalDevices(_handle, pPhysicalDeviceCount, pPhysicalDevices);
    }

    void InstanceContext::getPhysicalDeviceFeatures(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures* pFeatures) const
    {
        _vkGetPhysicalDeviceFeatures(physicalDevice, pFeatures);
    }

    void InstanceContext::getPhysicalDeviceProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties* pProperties) const
    {
        _vkGetPhysicalDeviceProperties(physicalDevice, pProperties);
    }

    void InstanceContext::getPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties* pQueueFamilyProperties) const
    {
        _vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
    }
}
