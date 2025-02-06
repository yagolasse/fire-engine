#include "window.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>

#include "assertion.h"
#include "renderer.h"

int Window::width;
int Window::height;

Window::Window(int width, int height, const char* title) {
    Window::width = width;
    Window::height = height;

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

    glfwSetFramebufferSizeCallback(handle, [](GLFWwindow* windowHandle, int newWidth, int newHeight) {
        Window::width = newWidth;
        Window::height = newHeight;
        Renderer::setViewport(0, 0, newWidth, newHeight);
    });

    //  1 -> 1 Frame V-Sync On
    //  0 -> V-Sync Off
    // -1 -> Adaptative Sync On

    glfwSwapInterval(-1);

    glfwShowWindow(handle);
}

Window::~Window() {
    glfwSetErrorCallback(NULL);

    glfwSetFramebufferSizeCallback(handle, NULL);

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

GLFWwindow* Window::getHandle() const {
    return handle;
}

int Window::getWidth() {
    return width;
}

int Window::getHeight() {
    return width;
}
