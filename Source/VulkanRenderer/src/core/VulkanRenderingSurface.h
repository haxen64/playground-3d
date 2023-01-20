#pragma once

#include <generic_renderer/core/IRenderingSurface.h>
#include <windows.h>

namespace vulkan_renderer::core
{
    class VulkanRenderingSurface : public generic_renderer::core::IRenderingSurface
    {
    public:
        VulkanRenderingSurface(HWND hwnd);

    private:
        HWND _hwnd;
    };
}
