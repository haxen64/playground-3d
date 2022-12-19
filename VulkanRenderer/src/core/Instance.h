#pragma once

#include <memory>
#include <optional>
#include <vector>
#include <vulkan/vulkan.h>
#include <windows.h>

#include <common/utils/SmartWrapper.h>

#include "contexts/InstanceContext.h"
#include "core/Device.h"
#include "core/PhysicalDevice.h"
#include "core/PhysicalDeviceType.h"

namespace vulkan_renderer::core
{
    class Instance
    {
    public:
        Instance();

        PhysicalDevice getPhysicalDevice(const std::optional<PhysicalDeviceType> preferredType = std::nullopt) const;

        Device* createDevice(const PhysicalDevice& physicalDevice);

    private:
        std::unique_ptr<contexts::InstanceContext> _context;
        common::utils::SmartWrapper<HMODULE> _vulkanLibHandle;
        common::utils::SmartWrapper<VkInstance> _handle;

        std::vector<std::unique_ptr<Device>> _devices;
    };
}
