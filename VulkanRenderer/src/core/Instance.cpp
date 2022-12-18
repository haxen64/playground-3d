#include "core/Instance.h"

#include <stdexcept>
#include <vector>

namespace vulkan_renderer::core
{
    Instance::Instance()
        : _context(contexts::InstanceContext())
    {
    }

    PhysicalDevice Instance::getPhysicalDevice(const std::optional<PhysicalDeviceType> preferredType) const
    {
        uint32_t physicalDeviceCount;
        _context.enumeratePhysicalDevices(&physicalDeviceCount, nullptr);

        std::vector<VkPhysicalDevice> rawPhysicalDevices(physicalDeviceCount);
        _context.enumeratePhysicalDevices(&physicalDeviceCount, rawPhysicalDevices.data());

        if (rawPhysicalDevices.empty())
            throw std::runtime_error("Failed to find a physical device with Vulkan support.");

        std::vector<PhysicalDevice> physicalDevices;

        for (const auto& rawPhysicalDevice : rawPhysicalDevices)
        {
            physicalDevices.push_back(PhysicalDevice(&_context, rawPhysicalDevice));
            if (!preferredType.has_value() || physicalDevices.back().getType() == preferredType)
                return physicalDevices.back();
        }

        return physicalDevices.front();
    }
}
