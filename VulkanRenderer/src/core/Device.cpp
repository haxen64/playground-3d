#include "core/Device.h"

namespace vulkan_renderer::core
{
    Device::Device(const contexts::InstanceContext* context, VkDevice handle)
        : _instanceContext(context), _context(std::make_unique<contexts::DeviceContext>(context, handle)), _handle(handle)
    {
    }

    Device::~Device()
    {
        if (_context)
            _instanceContext->destroyDevice(_handle, nullptr);
    }
}
