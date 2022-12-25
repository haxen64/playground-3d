#include "vulkan_wrapper/core/Device.h"

#include <stdexcept>

namespace vulkan_wrapper::core
{
    Device::Device(
        const contexts::InstanceContext* context,
        VkDevice handle,
        const std::vector<std::pair<QueueFamilyProperties, QueueCreationDetails>>& queueCreationDetailsList)
        : _instanceContext(context), _context(std::make_unique<contexts::DeviceContext>(context, handle)), _handle(handle)
    {
        for (const auto& queueCreationDetails : queueCreationDetailsList)
        {
            const auto& queueProperties = queueCreationDetails.first;
            const auto& creationDetails = queueCreationDetails.second;

            _queuesMap[queueProperties.getId()] = std::vector<Queue>();

            for (uint32_t i = 0; i < creationDetails.getCount(); ++i)
            {
                VkQueue handle;
                _context->getDeviceQueue(queueProperties.getId(), i, &handle);
                _queuesMap[queueProperties.getId()].push_back(Queue(handle));
            }
        }
    }

    Device::~Device()
    {
        if (_context)
            _instanceContext->destroyDevice(_handle, nullptr);
    }

    const std::vector<Queue>& Device::getQueues(const QueueFamilyProperties& queueFamilyProperties) const
    {
        auto queues = _queuesMap.find(queueFamilyProperties.getId());

        if (queues == _queuesMap.end())
            throw std::invalid_argument("Failed to get queues vector.");
        else
            return queues->second;
    }
}
