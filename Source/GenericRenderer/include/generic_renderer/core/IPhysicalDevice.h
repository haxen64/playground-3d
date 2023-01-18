#pragma once

namespace generic_renderer::core
{
    class IPhysicalDevice
    {
    public:
        virtual const char* getName() const = 0;
    };
}
