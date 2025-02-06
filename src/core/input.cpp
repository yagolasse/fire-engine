#include "input.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

GLFWwindow* Input::windowHandle;

void Input::init(GLFWwindow* windowHandle) {
    Input::windowHandle = windowHandle;
}

void Input::dispose() {
}

bool Input::isKeyPressed(Input::Key key) {
    return glfwGetKey(Input::windowHandle, (int)key) == GLFW_PRESS;
}

bool Input::isKeyReleased(Input::Key key) {
    return glfwGetKey(Input::windowHandle, (int)key) == GLFW_RELEASE;
}

Input::Input() {
}

Input::~Input() {
}