#include "core/Instance.h"

#include <stdexcept>
#include <vector>

#include "helpers/Interoperability.h"

namespace vulkan_renderer::core
{
    Instance::Instance()
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

        _context = std::make_unique<contexts::InstanceContext>(handle, vkGetInstanceProcAddr);
    }

    PhysicalDevice Instance::getPhysicalDevice(const std::optional<PhysicalDeviceType> preferredType) const
    {
        uint32_t physicalDeviceCount;
        _context->enumeratePhysicalDevices(&physicalDeviceCount, nullptr);

        std::vector<VkPhysicalDevice> rawPhysicalDevices(physicalDeviceCount);
        _context->enumeratePhysicalDevices(&physicalDeviceCount, rawPhysicalDevices.data());

        if (rawPhysicalDevices.empty())
            throw std::runtime_error("Failed to find a physical device with Vulkan support.");

        std::vector<PhysicalDevice> physicalDevices;

        for (const auto& rawPhysicalDevice : rawPhysicalDevices)
        {
            physicalDevices.push_back(PhysicalDevice(_context.get(), rawPhysicalDevice));
            if (!preferredType.has_value() || physicalDevices.back().getType() == preferredType)
                return physicalDevices.back();
        }

        return physicalDevices.front();
    }

    Device* Instance::createDevice(const PhysicalDevice& physicalDevice)
    {
        _devices.push_back(std::make_unique<Device>(_context.get(), nullptr));
        return _devices.back().get();
    }
}
