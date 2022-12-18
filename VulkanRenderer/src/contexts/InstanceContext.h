#pragma once

#include <vulkan/vulkan.h>
#include <windows.h>

#include <common/utils/SmartWrapper.h>

namespace vulkan_renderer::contexts
{
    class InstanceContext
    {
    public:
        InstanceContext();

        InstanceContext(const InstanceContext&) = delete;
        InstanceContext& operator=(const InstanceContext&) = delete;

        void* getInstanceProcAddr(const char* pName) const;
        VkResult enumeratePhysicalDevices(uint32_t* pPhysicalDeviceCount, VkPhysicalDevice* pPhysicalDevices) const;

    private:
        common::utils::SmartWrapper<HMODULE> _vulkanLibHandle;
        common::utils::SmartWrapper<VkInstance> _handle;

        PFN_vkGetInstanceProcAddr _vkGetInstanceProcAddr;
        PFN_vkEnumeratePhysicalDevices _vkEnumeratePhysicalDevices;

        void loadFunctions();
    };
}
