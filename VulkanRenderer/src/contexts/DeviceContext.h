#pragma once

#include "contexts/InstanceContext.h"

namespace vulkan_renderer::contexts
{
    class DeviceContext
    {
    public:
        DeviceContext(const InstanceContext* context, VkDevice handle);

    private:
        const InstanceContext* _context;
        VkDevice _handle;
    };
}
