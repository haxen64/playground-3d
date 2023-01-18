#pragma once

#include <vulkan/vulkan.h>

namespace vulkan_wrapper::core
{
    class Queue
    {
    public:
        Queue(VkQueue handle);

    private:
        VkQueue _handle;
    };
}
