#pragma once

#include <GLFW/glfw3.h>

class DebugUi {
   public:
    static void init(GLFWwindow* window);
    static void beginFrame();
    static void draw();
    static void dispose();
};
