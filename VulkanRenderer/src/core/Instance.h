#pragma once

#include <memory>
#include <utility>
#include <vector>
#include <vulkan/vulkan.h>
#include <windows.h>

#include <common/utils/SmartWrapper.h>

#include "contexts/InstanceContext.h"
#include "core/Device.h"
#include "core/DeviceCreationDetails.h"
#include "core/PhysicalDevice.h"
#include "core/PhysicalDeviceType.h"
#include "core/QueueCreationDetails.h"
#include "core/QueueFamilyProperties.h"

namespace vulkan_renderer::core
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
