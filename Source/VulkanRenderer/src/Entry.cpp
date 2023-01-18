#include "Entry.h"

#include "core/VulkanRenderingEnvironment.h"

generic_renderer::core::IRenderingEnvironment* createRenderingEnvironment()
{
    return new vulkan_renderer::core::VulkanRenderingEnvironment();
}
