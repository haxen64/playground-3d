#pragma once

#include <generic_renderer/core/IRenderingEnvironment.h>

extern "C"
{
    __declspec(dllexport) generic_renderer::core::IRenderingEnvironment* createRenderingEnvironment();
}
