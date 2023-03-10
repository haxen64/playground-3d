#include "vulkan_wrapper/core/Instance.h"

#include <stdexcept>
#include <common/helpers/Interoperability.h>

namespace vulkan_wrapper::core
{
    Instance::Instance()
    {
        _vulkanLibHandle = common::helpers::Interoperability::LoadWindowsLibrary("vulkan-1.dll");

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

        if (VK_SUCCESS != vkCreateInstance(&createInfo, nullptr, &handle))
            throw std::runtime_error("Failed to create a vulkan instance.");

        _handle = common::utils::SmartWrapper<VkInstance>(
            handle,
            [=](VkInstance h) { ((PFN_vkDestroyInstance)vkGetInstanceProcAddr(h, "vkDestroyInstance"))(h, nullptr); });

        _context = std::make_unique<contexts::InstanceContext>(handle, vkGetInstanceProcAddr);
    }

    std::vector<const PhysicalDevice*> Instance::getPhysicalDevices() const
    {
        if (!_physicalDevices.has_value())
        {
            uint32_t physicalDeviceCount;
            _context->enumeratePhysicalDevices(&physicalDeviceCount, nullptr);

            std::vector<VkPhysicalDevice> rawPhysicalDevices(physicalDeviceCount);
            _context->enumeratePhysicalDevices(&physicalDeviceCount, rawPhysicalDevices.data());

            _physicalDevices = std::vector<std::unique_ptr<PhysicalDevice>>();
            for (const auto& rawPhysicalDevice : rawPhysicalDevices)
                _physicalDevices.value().push_back(std::make_unique<PhysicalDevice>(_context.get(), rawPhysicalDevice));
        }

        std::vector<const PhysicalDevice*> physicalDevicePointers;
        for (const auto& physicalDevice : _physicalDevices.value())
            physicalDevicePointers.push_back(physicalDevice.get());

        return physicalDevicePointers;
    }

    Device* Instance::createDevice(
        const PhysicalDevice* physicalDevice,
        const auxiliary::DeviceCreationDetails& deviceCreationDetails,
        const std::vector<std::pair<auxiliary::QueueFamilyProperties, auxiliary::QueueCreationDetails>>& queueCreationDetailsList)
    {
        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        queueCreateInfos.reserve(queueCreationDetailsList.size());

        for (const auto& queueCreationDetails : queueCreationDetailsList)
        {
            const auto& queueProperties = queueCreationDetails.first;
            const auto& creationDetails = queueCreationDetails.second;

            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueProperties.getId();
            queueCreateInfo.queueCount = creationDetails.getCount();
            queueCreateInfo.pQueuePriorities = creationDetails.getPriorities().data();

            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkPhysicalDeviceFeatures physicalDeviceFeatures{};

        VkDeviceCreateInfo deviceCreateInfo{};
        deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
        deviceCreateInfo.pEnabledFeatures = &physicalDeviceFeatures;

        VkDevice handle;

        if (VK_SUCCESS != _context->createDevice(physicalDevice->getHandle(), &deviceCreateInfo, nullptr, &handle))
            throw std::runtime_error("Failed to create a logical device.");

        _devices.push_back(std::make_unique<Device>(_context.get(), handle, queueCreationDetailsList));
        return _devices.back().get();
    }
}
