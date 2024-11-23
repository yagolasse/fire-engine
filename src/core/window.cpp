#include "window.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>

#include "assertion.h"
#include "renderer.h"

Window::Window(int width, int height, const char* title) {
    glfwSetErrorCallback(Window::errorCallback);

    ASSERT_MSG(glfwInit(), "Could not initialize GLFW!");

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    handle = glfwCreateWindow(width, height, title, NULL, NULL);

    ASSERT_MSG(handle, "Could not create window!");

    int windowWitdh;
    int windowHeight;

    glfwGetWindowSize(handle, &windowWitdh, &windowHeight);

    const GLFWvidmode* videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    if (videoMode) {
        int xPosition = (videoMode->width - windowWitdh) / 2;
        int yPosition = (videoMode->height - windowHeight) / 2;
        glfwSetWindowPos(handle, xPosition, yPosition);
    }

    glfwMakeContextCurrent(handle);

    glfwSetFramebufferSizeCallback(handle, [](GLFWwindow *windowHandle, int width, int height) {
        Renderer::setViewport(0, 0, width, height);
    });

    glfwSwapInterval(0);

    glfwShowWindow(handle);
}

Window::~Window() {
    glfwSetErrorCallback(NULL);
    glfwDestroyWindow(handle);

    glfwTerminate();
}

void Window::errorCallback(int errorCode, const char* description) {
    std::cerr << "Error" << errorCode << ": " << description;
}

void Window::swapBuffers() const {
    glfwSwapBuffers(handle);
}

void Window::pollEvents() const {
    glfwPollEvents();
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(handle);
}
