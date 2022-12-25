#include "vulkan_wrapper/core/Queue.h"

namespace vulkan_wrapper::core
{
    Queue::Queue(VkQueue handle)
        : _handle(handle)
    {
    }
}
