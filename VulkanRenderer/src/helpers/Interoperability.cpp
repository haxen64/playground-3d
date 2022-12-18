#include "helpers/Interoperability.h"

#include <format>
#include <stdexcept>

namespace vulkan_renderer::helpers
{
    common::utils::SmartWrapper<HMODULE> Interoperability::LoadWindowsLibrary(const char* libFileName)
    {
        HMODULE handle = LoadLibraryA(libFileName);

        if (handle == nullptr)
            throw std::runtime_error(std::format("Failed to load the specified library. ({})", libFileName));

        return common::utils::SmartWrapper<HMODULE>(handle, [](HMODULE h) { FreeLibrary(h); });
    }
}
