#pragma once

#include <optional>

#include "contexts/InstanceContext.h"
#include "core/PhysicalDevice.h"
#include "core/PhysicalDeviceType.h"

namespace vulkan_renderer::core
{
    class Instance
    {
    public:
        Instance();

        PhysicalDevice getPhysicalDevice(const std::optional<PhysicalDeviceType> preferredType = std::nullopt) const;

    private:
        contexts::InstanceContext _context;
    };
}
