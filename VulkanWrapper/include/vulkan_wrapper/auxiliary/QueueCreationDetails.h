#pragma once

#include <cstdint>
#include <vector>

namespace vulkan_wrapper::auxiliary
{
    class QueueCreationDetails
    {
    public:
        QueueCreationDetails(uint32_t count, const std::vector<float>& priorities);

        uint32_t getCount() const;
        const std::vector<float>& getPriorities() const;

    private:
        uint32_t _count;
        std::vector<float> _priorities;
    };
}
