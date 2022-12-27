#include <common/helpers/Interoperability.h>

int main()
{
    auto vulkanRendererLibHandle = common::helpers::Interoperability::LoadWindowsLibrary("vulkan_renderer.dll");
    auto test = (void(*)())GetProcAddress(vulkanRendererLibHandle.value(), "test");
    test();
    return 0;
}
