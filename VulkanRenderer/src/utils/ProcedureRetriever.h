#pragma once

#include <functional>
#include <optional>
#include <string>

namespace vulkan_renderer::utils
{
    class ProcedureRetriever
    {
    public:
        static ProcedureRetriever LoadWindowsLibrary(const std::string& libraryFileName);

        ProcedureRetriever() = default;
        ProcedureRetriever(std::function<void* (const std::string&)> getProcAddrFunction,
                           std::function<void()> releaseFunction);
        ~ProcedureRetriever();

        ProcedureRetriever(const ProcedureRetriever&) = delete;
        ProcedureRetriever(ProcedureRetriever&& procedureRetriever) noexcept;
        ProcedureRetriever& operator=(const ProcedureRetriever&) = delete;
        ProcedureRetriever& operator=(ProcedureRetriever&& procedureRetriever) noexcept;

        void* getProcAddress(const std::string& procName) const;

    private:
        std::optional<std::function<void* (const std::string&)>> _getProcAddrFunction;
        std::optional<std::function<void()>> _releaseFunction;
    };
}
