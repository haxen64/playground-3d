#include "contexts/VulkanInstanceContext.h"

#include <stdexcept>
#include <vulkan/vulkan.h>

namespace vulkan_renderer::contexts
{
	VulkanInstanceContext::VulkanInstanceContext()
        : _vkProcedureRetriever(utils::ProcedureRetriever::LoadWindowsLibrary("vulkan-1.dll"))
    {
        PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)_vkProcedureRetriever.getProcAddress("vkGetInstanceProcAddr");
        PFN_vkCreateInstance vkCreateInstance = (PFN_vkCreateInstance)vkGetInstanceProcAddr(nullptr, "vkCreateInstance");

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Vulkan Renderer";
        appInfo.applicationVersion = VK_MAKE_API_VERSION(0, 1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        if (vkCreateInstance(&createInfo, nullptr, &_vkInstance) != VK_SUCCESS)
            throw std::runtime_error("Failed to create a vulkan instance.");

        _vkInstanceProcedureRetriever = utils::ProcedureRetriever(
            [=](const std::string& procName) { return vkGetInstanceProcAddr(_vkInstance, procName.c_str()); },
            [=]() { ((PFN_vkDestroyInstance)vkGetInstanceProcAddr(_vkInstance, "vkDestroyInstance"))(_vkInstance, nullptr); }
        );

        loadFunctions();
    }

    VkResult VulkanInstanceContext::enumeratePhysicalDevices(uint32_t* pPhysicalDeviceCount, VkPhysicalDevice* pPhysicalDevices)
    {
        return _vkEnumeratePhysicalDevices(_vkInstance, pPhysicalDeviceCount, pPhysicalDevices);
    }

	void VulkanInstanceContext::loadFunctions()
	{
        _vkEnumeratePhysicalDevices = (PFN_vkEnumeratePhysicalDevices)_vkInstanceProcedureRetriever.getProcAddress("vkEnumeratePhysicalDevices");
	}
}
