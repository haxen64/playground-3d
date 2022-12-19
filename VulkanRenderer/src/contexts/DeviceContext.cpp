#include "contexts/DeviceContext.h"

namespace vulkan_renderer::contexts
{
    DeviceContext::DeviceContext(const InstanceContext* context, VkDevice handle)
        : _context(context), _handle(handle)
    {
    }
}
