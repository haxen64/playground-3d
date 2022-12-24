#pragma once

#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>
#include <vulkan/vulkan.h>

#include "contexts/DeviceContext.h"
#include "contexts/InstanceContext.h"
#include "core/Queue.h"
#include "core/QueueCreationDetails.h"
#include "core/QueueFamilyProperties.h"

namespace vulkan_renderer::core
{
    class Device
    {
    public:
        Device(
            const contexts::InstanceContext* context,
            VkDevice handle,
            const std::vector<std::pair<QueueFamilyProperties, QueueCreationDetails>>& queueCreationDetailsList);
        ~Device();

        const std::vector<Queue>& getQueues(const QueueFamilyProperties& queueFamilyProperties) const;

    private:
        const contexts::InstanceContext* _instanceContext;
        std::unique_ptr<contexts::DeviceContext> _context;
        VkDevice _handle;

        std::unordered_map<uint32_t, std::vector<Queue>> _queuesMap;
    };
}
