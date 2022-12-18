#pragma once

#include <functional>

namespace common::utils
{
    class ProcedureRetriever
    {
    public:
        ProcedureRetriever();
        ProcedureRetriever(std::function<void* (const char*)> getProcedureAddressFunction);

        void* getProcedureAddress(const char* procedureName) const;

    private:
        std::function<void* (const char*)> _getProcedureAddressFunction;
    };
}
