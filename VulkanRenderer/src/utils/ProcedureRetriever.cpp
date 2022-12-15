#include "utils/ProcedureRetriever.h"

#include <stdexcept>
#include <utility>
#include <windows.h>

namespace vulkan_renderer::utils
{
    ProcedureRetriever ProcedureRetriever::LoadWindowsLibrary(const std::string& libraryFileName)
    {
        HMODULE libraryPointer = LoadLibraryA(libraryFileName.c_str());

        if (libraryPointer == nullptr)
            throw new std::runtime_error("Failed to load the specified library.");

        return ProcedureRetriever(
            [=](const std::string& procAddress) { return GetProcAddress(libraryPointer, procAddress.c_str()); },
            [=]() { FreeLibrary(libraryPointer); });
    }

    ProcedureRetriever::ProcedureRetriever(std::function<void* (const std::string&)> getProcAddrFunction, std::function<void()> releaseFunction)
        : _getProcAddrFunction(getProcAddrFunction), _releaseFunction(releaseFunction)
    {
    }

    ProcedureRetriever::~ProcedureRetriever()
    {
        if (_releaseFunction.has_value())
            _releaseFunction.value()();
    }

    ProcedureRetriever::ProcedureRetriever(ProcedureRetriever&& procedureRetriever) noexcept
    {
        std::swap(_getProcAddrFunction, procedureRetriever._getProcAddrFunction);
        std::swap(_releaseFunction, procedureRetriever._releaseFunction);
    }

    ProcedureRetriever& ProcedureRetriever::operator=(ProcedureRetriever procedureRetriever)
    {
        std::swap(_getProcAddrFunction, procedureRetriever._getProcAddrFunction);
        std::swap(_releaseFunction, procedureRetriever._releaseFunction);
        return *this;
    }

    void* ProcedureRetriever::getProcAddress(const std::string& procName) const
    {
        if (!_getProcAddrFunction.has_value())
            throw std::runtime_error("The procedure retriever is moved or not initialized.");

        auto procAddress = _getProcAddrFunction.value()(procName.c_str());

        if (procAddress == nullptr)
            throw new std::runtime_error("Failed to retrieve the requested procedure.");

        return procAddress;
    }
}
