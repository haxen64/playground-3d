#pragma once

#include "vulkan_wrapper/auxiliary/QueueCreationDetails.h"
#include "vulkan_wrapper/auxiliary/QueueFamilyProperties.h"
#include "vulkan_wrapper/contexts/DeviceContext.h"
#include "vulkan_wrapper/contexts/InstanceContext.h"
#include "vulkan_wrapper/core/Queue.h"

#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>
#include <vulkan/vulkan.h>

namespace vulkan_wrapper::core
{
    class Device
    {
    public:
        Device(
            const contexts::InstanceContext* context,
            VkDevice handle,
            const std::vector<std::pair<auxiliary::QueueFamilyProperties, auxiliary::QueueCreationDetails>>& queueCreationDetailsList);
        ~Device();

        const std::vector<Queue>& getQueues(const auxiliary::QueueFamilyProperties& queueFamilyProperties) const;

    private:
        const contexts::InstanceContext* _instanceContext;
        std::unique_ptr<contexts::DeviceContext> _context;
        VkDevice _handle;

        std::unordered_map<uint32_t, std::vector<Queue>> _queuesMap;
    };
}
