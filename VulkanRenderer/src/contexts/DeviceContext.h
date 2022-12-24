#pragma once

#include <vulkan/vulkan.h>
#include <common/utils/ProcedureRetriever.h>
#include "contexts/InstanceContext.h"

namespace vulkan_renderer::contexts
{
    class DeviceContext
    {
    public:
        DeviceContext(const InstanceContext* context, VkDevice handle);

        void* getDeviceProcAddr(const char* pName) const;

        void getDeviceQueue(uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* pQueue) const;

    private:
        const InstanceContext* _context;
        VkDevice _handle;
        common::utils::ProcedureRetriever _vkDeviceProcedureRetriever;

        PFN_vkGetDeviceQueue _vkGetDeviceQueue;
    };
}
