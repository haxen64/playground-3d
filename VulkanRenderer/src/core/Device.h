#pragma once

#include <memory>
#include <vulkan/vulkan.h>

#include "contexts/DeviceContext.h"
#include "contexts/InstanceContext.h"

namespace vulkan_renderer::core
{
    class Device
    {
    public:
        Device(const contexts::InstanceContext* context, VkDevice handle);
        ~Device();

    private:
        const contexts::InstanceContext* _instanceContext;
        std::unique_ptr<contexts::DeviceContext> _context;
        VkDevice _handle;
    };
}
