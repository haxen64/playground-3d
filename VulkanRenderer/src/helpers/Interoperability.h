#pragma once

#include <windows.h>
#include <common/utils/SmartWrapper.h>

namespace vulkan_renderer::helpers
{
    class Interoperability
    {
    public:
        static common::utils::SmartWrapper<HMODULE> LoadWindowsLibrary(const char* libFileName);

    private:
        Interoperability() = delete;
    };
}
