#include "input.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

GLFWwindow* Input::windowHandle;
void (*Input::keyCallback)(Input::Key, Input::KeyEventType);

void Input::init(GLFWwindow* windowHandle) {
    Input::windowHandle = windowHandle;
    glfwSetKeyCallback(windowHandle, Input::onKeyPressed);
}

void Input::dispose() {
    glfwSetKeyCallback(windowHandle, NULL);
}

bool Input::isKeyPressed(Input::Key key) {
    return glfwGetKey(Input::windowHandle, (int)key) == GLFW_PRESS;
}

bool Input::isKeyReleased(Input::Key key) {
    return glfwGetKey(Input::windowHandle, (int)key) == GLFW_RELEASE;
}

void Input::addKeyPressedCallback(void (*callback)(Input::Key, Input::KeyEventType)) {
    Input::keyCallback = callback;
}

Input::Input() {
}

Input::~Input() {
}

void Input::onKeyPressed(GLFWwindow* windowHandle, int key, int scancode, int action, int mods) {
    Input::keyCallback((Input::Key)key, action == GLFW_RELEASE ? Input::KeyEventType::RELEASED : Input::KeyEventType::PRESSED);
}
