#pragma once

#include "generic_renderer/core/IPhysicalDevice.h"

namespace generic_renderer::core
{
    class IRenderingEnvironment
    {
    public:
        virtual void release() = 0;
        
        virtual const IPhysicalDevice** getAvailablePhysicalDevices() = 0;
        virtual void test() = 0;
    };
}
