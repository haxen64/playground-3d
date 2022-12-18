#include "utils/ProcedureRetriever.h"

#include <format>
#include <stdexcept>

namespace common::utils
{
    ProcedureRetriever::ProcedureRetriever()
    {
    }

    ProcedureRetriever::ProcedureRetriever(std::function<void* (const char*)> getProcedureAddressFunction)
        : _getProcedureAddressFunction(getProcedureAddressFunction)
    {
    }

    void* ProcedureRetriever::getProcedureAddress(const char* procedureName) const
    {
        auto procedurePointer = _getProcedureAddressFunction ? _getProcedureAddressFunction(procedureName) : nullptr;

        if (procedurePointer == nullptr)
            throw std::runtime_error(std::format("Failed to retrieve the \"{}\" procedure.", procedureName));

        return procedurePointer;
    }
}
