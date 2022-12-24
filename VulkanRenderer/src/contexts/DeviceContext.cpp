#include "contexts/DeviceContext.h"

namespace vulkan_renderer::contexts
{
    DeviceContext::DeviceContext(const InstanceContext* context, VkDevice handle)
        : _context(context), _handle(handle)
    {
        auto vkGetDeviceProcAddr = (PFN_vkGetDeviceProcAddr)_context->getInstanceProcAddr("vkGetDeviceProcAddr");
        _vkDeviceProcedureRetriever = common::utils::ProcedureRetriever([=](const char* procedureName) { return vkGetDeviceProcAddr(handle, procedureName); });

        _vkGetDeviceQueue = (PFN_vkGetDeviceQueue)getDeviceProcAddr("vkGetDeviceQueue");
    }

    void* DeviceContext::getDeviceProcAddr(const char* pName) const
    {
        return _vkDeviceProcedureRetriever.getProcedureAddress(pName);
    }

    void DeviceContext::getDeviceQueue(uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* pQueue) const
    {
        _vkGetDeviceQueue(_handle, queueFamilyIndex, queueIndex, pQueue);
    }
}
