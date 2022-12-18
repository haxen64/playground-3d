#include "contexts/InstanceContext.h"

#include <stdexcept>
#include "helpers/Interoperability.h"

namespace vulkan_renderer::contexts
{
    InstanceContext::InstanceContext()
    {
        _vulkanLibHandle = helpers::Interoperability::LoadWindowsLibrary("vulkan-1.dll");

        PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)GetProcAddress(_vulkanLibHandle.value(), "vkGetInstanceProcAddr");
        PFN_vkCreateInstance vkCreateInstance = (PFN_vkCreateInstance)vkGetInstanceProcAddr(nullptr, "vkCreateInstance");

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Vulkan Renderer";
        appInfo.applicationVersion = VK_MAKE_API_VERSION(0, 1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        VkInstance handle;

        if (vkCreateInstance(&createInfo, nullptr, &handle) != VK_SUCCESS)
            throw std::runtime_error("Failed to create a vulkan instance.");

        _handle = common::utils::SmartWrapper<VkInstance>(
            handle,
            [=](VkInstance h) { ((PFN_vkDestroyInstance)vkGetInstanceProcAddr(h, "vkDestroyInstance"))(h, nullptr); });

        _vkGetInstanceProcAddr = vkGetInstanceProcAddr;
        loadFunctions();
    }

    void* InstanceContext::getInstanceProcAddr(const char* pName) const
    {
        return _vkGetInstanceProcAddr(_handle.value(), pName);
    }

    VkResult InstanceContext::enumeratePhysicalDevices(uint32_t* pPhysicalDeviceCount, VkPhysicalDevice* pPhysicalDevices) const
    {
        return _vkEnumeratePhysicalDevices(_handle.value(), pPhysicalDeviceCount, pPhysicalDevices);
    }

    void InstanceContext::loadFunctions()
    {
        _vkEnumeratePhysicalDevices = (PFN_vkEnumeratePhysicalDevices)getInstanceProcAddr("vkEnumeratePhysicalDevices");
    }
}
