#include <iostream>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h> 

#include "Window.hpp"

void error_callback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW globally!" << std::endl;
        return -1;
    }

    glfwSetErrorCallback([](int error, const char* description) {
        std::cerr << "GLFW Global Error " << error << ": " << description << std::endl;
    });

    Window myWindow("My OpenGL Game", 1280, 720);

    if (myWindow.isValid()) {
        glfwSetFramebufferSizeCallback(myWindow.getGLFWwindow(), [](GLFWwindow* window, int width, int height) {
            glViewport(0, 0, width, height);
            std::cout << "Framebuffer resized to " << width << "x" << height << std::endl;
        });

        while (!myWindow.shouldClose()) {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            //Code 

            myWindow.swapBuffers();
            Window::pollEvents(); 
        }
    }

    glfwTerminate();
    return 0;
}