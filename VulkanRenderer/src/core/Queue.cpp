#include "core/Queue.h"

namespace vulkan_renderer::core
{
    Queue::Queue(VkQueue handle)
        : _handle(handle)
    {
    }
}
