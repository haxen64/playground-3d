#pragma once

#include "vulkan_wrapper/auxiliary/DeviceCreationDetails.h"
#include "vulkan_wrapper/auxiliary/PhysicalDeviceType.h"
#include "vulkan_wrapper/auxiliary/QueueCreationDetails.h"
#include "vulkan_wrapper/auxiliary/QueueFamilyProperties.h"
#include "vulkan_wrapper/contexts/InstanceContext.h"
#include "vulkan_wrapper/core/Device.h"
#include "vulkan_wrapper/core/PhysicalDevice.h"

#include <common/utils/SmartWrapper.h>

#include <memory>
#include <optional>
#include <utility>
#include <vector>
#include <vulkan/vulkan.h>
#include <windows.h>

namespace vulkan_wrapper::core
{
    class Instance
    {
    public:
        Instance();

        std::vector<const PhysicalDevice*> getPhysicalDevices() const;

        Device* createDevice(
            const PhysicalDevice* physicalDevice,
            const auxiliary::DeviceCreationDetails& deviceCreationDetails,
            const std::vector<std::pair<auxiliary::QueueFamilyProperties, auxiliary::QueueCreationDetails>>& queueCreationDetailsList);

    private:
        std::unique_ptr<contexts::InstanceContext> _context;
        common::utils::SmartWrapper<HMODULE> _vulkanLibHandle;
        common::utils::SmartWrapper<VkInstance> _handle;

        mutable std::optional<std::vector<std::unique_ptr<PhysicalDevice>>> _physicalDevices;
        std::vector<std::unique_ptr<Device>> _devices;
    };
}
