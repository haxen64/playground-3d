#include <iostream>
#include <stdexcept>
#include <vulkan_renderer/Test.h>

int main()
{
    try
    {
        vulkan_renderer::test();
    }
    catch (const std::exception& e)
    {
        std::cout << "An unhandled exception has been raised:" << std::endl << "\t" << e.what() << std::endl;
    }

    return 0;
}
