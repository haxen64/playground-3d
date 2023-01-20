#pragma once

#include "generic_renderer/core/IRenderingSurface.h"
#include <windows.h>

namespace generic_renderer::core
{
    class IRenderingWorld
    {
    public:
        virtual IRenderingSurface* createRenderingSurface(HWND hwnd) = 0;
    };
}
