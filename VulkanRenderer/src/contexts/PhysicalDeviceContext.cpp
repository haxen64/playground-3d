#include "PhysicalDeviceContext.h"

namespace vulkan_renderer::contexts
{
    PhysicalDeviceContext::PhysicalDeviceContext(const InstanceContext* instanceContext, VkPhysicalDevice handle)
        : _instanceContext(instanceContext), _handle(handle)
    {
    }

    void PhysicalDeviceContext::getPhysicalDeviceFeatures(VkPhysicalDeviceFeatures* pFeatures) const
    {
        _instanceContext->getPhysicalDeviceFeatures(_handle, pFeatures);
    }

    void PhysicalDeviceContext::getPhysicalDeviceProperties(VkPhysicalDeviceProperties* pProperties) const
    {
        _instanceContext->getPhysicalDeviceProperties(_handle, pProperties);
    }
}
