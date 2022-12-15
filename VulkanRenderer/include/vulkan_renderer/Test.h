#pragma once

#ifdef VULKAN_RENDERER_EXPORT
#define VulkanRendererExport __declspec(dllexport)
#else
#define VulkanRendererExport __declspec(dllimport)
#endif

namespace vulkan_renderer
{
    extern "C"
    {
        VulkanRendererExport void test();
    }
}
