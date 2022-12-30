#include "core/VulkanRenderingEnvironment.h"

#include <algorithm>
#include <stdexcept>

namespace vulkan_renderer::core
{
    VulkanRenderingEnvironment::VulkanRenderingEnvironment()
    {
        auto physicalDevices = _vulkanInstance.getPhysicalDevices();

        for (const auto& physicalDevice : physicalDevices)
            _physicalDevices.push_back(std::make_unique<VulkanPhysicalDevice>(physicalDevice));

        for (const auto& physicalDevice : _physicalDevices)
            _physicalDevicePointers.push_back(physicalDevice.get());

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

    generic_renderer::core::IWindow* VulkanRenderingEnvironment::createWindow(const generic_renderer::core::IPhysicalDevice* physicalDevice)
    {
        auto selectedPhysicalDevice = std::find_if(
            _physicalDevices.begin(),
            _physicalDevices.end(),
            [=](const std::unique_ptr<VulkanPhysicalDevice>& device) { return device.get() == physicalDevice; }
        );

        if (selectedPhysicalDevice == _physicalDevices.end())
            throw std::invalid_argument("Invalid physical device pointer.");

        auto physicalDeviceHandle = selectedPhysicalDevice->get()->getHandle();
        auto queueFamilyProperties = physicalDeviceHandle->getQueueFamilyProperties();

        const auto& graphicsQueueFamily = *std::find_if(
            queueFamilyProperties.begin(),
            queueFamilyProperties.end(),
            [](const vulkan_wrapper::auxiliary::QueueFamilyProperties& properties) { return properties.supportsGraphics(); });

        auto device = _vulkanInstance.createDevice(
            physicalDeviceHandle,
            vulkan_wrapper::auxiliary::DeviceCreationDetails(),
            { std::make_pair(graphicsQueueFamily, vulkan_wrapper::auxiliary::QueueCreationDetails(1, { 1.0f })) });

        _windows.push_back(std::make_unique<VulkanWindow>(device));
        return _windows.back().get();
    }
}
