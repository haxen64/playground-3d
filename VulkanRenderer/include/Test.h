#pragma once

#ifdef VULKAN_RENDERER_EXPORT
#define VulkanRendererExport __declspec(dllexport)
#else
#define VulkanRendererExport __declspec(dllimport)
#endif

extern "C" VulkanRendererExport int test();
