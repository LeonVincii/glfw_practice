#define GLFW_INCLUDE_VULKAN
#include <glfw3.h>

#include <stdexcept>

void errorCallback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

int main()
{
    // Initialise GLFW.
    if (!glfwInit())
        throw std::runtime_error("failed to initialise GLFW");

    // Set GLFW callbacks.
    glfwSetErrorCallback(errorCallback);

    // Do not create with OpenGL context.
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    // Create window.
    GLFWwindow* window = glfwCreateWindow(640, 480, "GLFW Window", nullptr, nullptr);

    if (!window)
        throw std::runtime_error("failed to create GLFW window");

    // Destroy window.
    glfwDestroyWindow(window);

    // Terminate GLFW.
    glfwTerminate();
    return 0;
}
