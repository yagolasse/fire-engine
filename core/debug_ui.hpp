#ifndef DEBUG_UI_HPP
#define DEBUG_UI_HPP

struct GLFWwindow;

class DebugUi {
   public:
    static void init(GLFWwindow* window);
    static void beginFrame();
    static void draw();
    static void dispose();
};

#endif
