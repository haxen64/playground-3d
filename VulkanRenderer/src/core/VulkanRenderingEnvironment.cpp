#include "core/VulkanRenderingEnvironment.h"

namespace vulkan_renderer::core
{
    VulkanRenderingEnvironment::VulkanRenderingEnvironment()
    {
        auto physicalDevices = _vulkanInstance.getPhysicalDevices();

        for (const auto& physicalDevice : physicalDevices)
            _physicalDevices.emplace_back(physicalDevice);

        for (const auto& physicalDevice : _physicalDevices)
            _physicalDevicePointers.push_back(&physicalDevice);

        _physicalDevicePointers.push_back(nullptr);
    }

    void VulkanRenderingEnvironment::release()
    {
        delete this;
    }

    const generic_renderer::core::IPhysicalDevice** VulkanRenderingEnvironment::getAvailablePhysicalDevices()
    {
        return _physicalDevicePointers.data();
    }

    void VulkanRenderingEnvironment::test()
    {
        /*try
        {
            vulkan_wrapper::core::Instance instance;
            auto physicalDevices = instance.getPhysicalDevices();

            const auto& discretePhysicalDevice = *std::find_if(
                physicalDevices.begin(),
                physicalDevices.end(),
                [](const vulkan_wrapper::core::PhysicalDevice* physicalDevice) { return physicalDevice->getType() == vulkan_wrapper::auxiliary::PhysicalDeviceType::DiscreteGpu; }
            );

            auto queueFamilyProperties = discretePhysicalDevice->getQueueFamilyProperties();

            const auto& graphicsQueueFamily = *std::find_if(
                queueFamilyProperties.begin(),
                queueFamilyProperties.end(),
                [](const vulkan_wrapper::auxiliary::QueueFamilyProperties& properties) { return properties.supportsGraphics(); });

            auto device = instance.createDevice(
                discretePhysicalDevice,
                vulkan_wrapper::auxiliary::DeviceCreationDetails(),
                { std::make_pair(graphicsQueueFamily, vulkan_wrapper::auxiliary::QueueCreationDetails(1, { 1.0f })) });

            const auto& graphicsQueue = device->getQueues(graphicsQueueFamily).front();
        }
        catch (const std::exception& e)
        {
            std::cout << "An unhandled exception has been raised:" << std::endl << "\t" << e.what() << std::endl;
        }*/
    }
}
