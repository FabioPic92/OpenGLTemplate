#include <string>
#include <stdexcept>
#include <iostream>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class Window {
private:
    std::string m_name;

    int m_sizeX;
    int m_sizeY;

    GLFWwindow* m_window;

public:
    Window(const std::string &name, int sizeX, int sizeY)
    :   m_name(name), m_sizeX(sizeX), m_sizeY(sizeY), m_window(nullptr)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE); 

        m_window = glfwCreateWindow(m_sizeX, m_sizeY, m_name.c_str(), NULL, NULL);
        if(!m_window){
            throw std::runtime_error("Failed to create GLFW window!"); 
        } else {
            glfwMakeContextCurrent(m_window);
         
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                    std::cerr << "ERROR: Failed to initialize GLAD for window '" << m_name << "'!" << std::endl;
                    glfwDestroyWindow(m_window);
                    m_window = nullptr;
                    throw std::runtime_error("Failed to initialize GLAD!");
            } else {
                std::cout << "GLAD initialized for window '" << m_name << "'." << std::endl;
                int initial_width, initial_height;
                glfwGetFramebufferSize(m_window, &initial_width, &initial_height);
                glViewport(0, 0, initial_width, initial_height);

                std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
                std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
            }
        }
    }

    ~Window() {
        if (m_window) {
            glfwDestroyWindow(m_window);
            std::cout << "Window '" << m_name << "' destroyed." << std::endl;
        }
    }

    inline bool isValid() const {
        return m_window != nullptr;
    }

    inline bool shouldClose() const {
        return m_window && glfwWindowShouldClose(m_window);
    }

    inline void swapBuffers() {
        if (m_window) {
            glfwSwapBuffers(m_window);
        }
    }

    static void pollEvents() {
        glfwPollEvents();
    }

    GLFWwindow* getGLFWwindow() const {
        return m_window;
    }
};