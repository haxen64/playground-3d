#pragma once

#include <windows.h>
#include <common/utils/SmartWrapper.h>

namespace vulkan_wrapper::helpers
{
    class Interoperability
    {
    public:
        static common::utils::SmartWrapper<HMODULE> LoadWindowsLibrary(const char* libFileName);

    private:
        Interoperability() = delete;
    };
}
