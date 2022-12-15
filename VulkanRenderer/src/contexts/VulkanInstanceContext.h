#pragma once

#include <vulkan/vulkan.h>
#include "utils/ProcedureRetriever.h"

namespace vulkan_renderer::contexts
{
	class VulkanInstanceContext
	{
	public:
		VulkanInstanceContext();

		VkResult enumeratePhysicalDevices(uint32_t* pPhysicalDeviceCount, VkPhysicalDevice* pPhysicalDevices);

	private:
		utils::ProcedureRetriever _vkProcedureRetriever;
		utils::ProcedureRetriever _vkInstanceProcedureRetriever;
		VkInstance _vkInstance;

		PFN_vkEnumeratePhysicalDevices _vkEnumeratePhysicalDevices;

		void loadFunctions();
	};
}
