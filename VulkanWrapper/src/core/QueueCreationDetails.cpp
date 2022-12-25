#include "vulkan_wrapper/core/QueueCreationDetails.h"

#include <stdexcept>

namespace vulkan_wrapper::core
{
    QueueCreationDetails::QueueCreationDetails(uint32_t count, const std::vector<float>& priorities)
        : _count(count), _priorities(priorities)
    {
        if (_count != _priorities.size())
            throw std::invalid_argument("Count and priorities vector's size should match.");
    }

    uint32_t QueueCreationDetails::getCount() const
    {
        return _count;
    }

    const std::vector<float>& QueueCreationDetails::getPriorities() const
    {
        return _priorities;
    }
}
