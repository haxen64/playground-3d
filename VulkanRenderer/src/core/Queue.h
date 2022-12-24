#pragma once

#include <vulkan/vulkan.h>

namespace vulkan_renderer::core
{
    class Queue
    {
    public:
        Queue(VkQueue handle);

    private:
        VkQueue _handle;
    };
}
