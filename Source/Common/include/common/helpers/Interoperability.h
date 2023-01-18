#pragma once

#include "common/utils/SmartWrapper.h"
#include <windows.h>

namespace common::helpers
{
    class Interoperability
    {
    public:
        static common::utils::SmartWrapper<HMODULE> LoadWindowsLibrary(const char* libFileName);

    private:
        Interoperability() = delete;
    };
}
