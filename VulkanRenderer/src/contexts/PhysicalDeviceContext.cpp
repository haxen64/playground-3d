#include "contexts/PhysicalDeviceContext.h"

namespace vulkan_renderer::contexts
{
    PhysicalDeviceContext::PhysicalDeviceContext(const InstanceContext* instanceContext, VkPhysicalDevice handle)
        : _instanceContext(instanceContext), _handle(handle)
    {
        loadFunctions();
    }

    void PhysicalDeviceContext::getPhysicalDeviceFeatures(VkPhysicalDeviceFeatures* pFeatures) const
    {
        _vkGetPhysicalDeviceFeatures(_handle, pFeatures);
    }

    void PhysicalDeviceContext::getPhysicalDeviceProperties(VkPhysicalDeviceProperties* pProperties) const
    {
        _vkGetPhysicalDeviceProperties(_handle, pProperties);
    }

    void PhysicalDeviceContext::loadFunctions()
    {
        _vkGetPhysicalDeviceFeatures = (PFN_vkGetPhysicalDeviceFeatures)_instanceContext->getInstanceProcAddr("vkGetPhysicalDeviceFeatures");
        _vkGetPhysicalDeviceProperties = (PFN_vkGetPhysicalDeviceProperties)_instanceContext->getInstanceProcAddr("vkGetPhysicalDeviceProperties");
    }
}
