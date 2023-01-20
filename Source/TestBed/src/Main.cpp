#include <common/helpers/Interoperability.h>
#include <generic_renderer/core/IRenderingEnvironment.h>

int main()
{
    auto vulkanRendererLibHandle = common::helpers::Interoperability::LoadWindowsLibrary("vulkan_renderer.dll");
    auto createRenderingEnvironment = (generic_renderer::core::IRenderingEnvironment * (*)())GetProcAddress(vulkanRendererLibHandle.value(), "createRenderingEnvironment");
    auto renderingEnvironment = createRenderingEnvironment();
    auto physicalDevice = *renderingEnvironment->getAvailablePhysicalDevices();
    auto renderingWorld = renderingEnvironment->createRenderingWorld(physicalDevice);
    auto renderingSurface = renderingWorld->createRenderingSurface(nullptr);
    renderingEnvironment->release();
    return 0;
}
