#pragma once

#include <memory>
#include <utility>
#include <vector>
#include <windows.h>

#include <vulkan/vulkan.h>

#include <common/utils/SmartWrapper.h>

#include "vulkan_wrapper/contexts/InstanceContext.h"
#include "vulkan_wrapper/core/Device.h"
#include "vulkan_wrapper/core/DeviceCreationDetails.h"
#include "vulkan_wrapper/core/PhysicalDevice.h"
#include "vulkan_wrapper/core/PhysicalDeviceType.h"
#include "vulkan_wrapper/core/QueueCreationDetails.h"
#include "vulkan_wrapper/core/QueueFamilyProperties.h"

namespace vulkan_wrapper::core
{
    class Instance
    {
    public:
        Instance();

        std::vector<PhysicalDevice> getPhysicalDevices() const;

        Device* createDevice(
            const PhysicalDevice& physicalDevice,
            const DeviceCreationDetails& deviceCreationDetails,
            const std::vector<std::pair<QueueFamilyProperties, QueueCreationDetails>>& queueCreationDetailsList);

    private:
        std::unique_ptr<contexts::InstanceContext> _context;
        common::utils::SmartWrapper<HMODULE> _vulkanLibHandle;
        common::utils::SmartWrapper<VkInstance> _handle;

        std::vector<std::unique_ptr<Device>> _devices;
    };
}
