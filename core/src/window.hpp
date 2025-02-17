#ifndef WINDOW_HPP
#define WINDOW_HPP

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class Window {
   private:
    GLFWwindow* handle;
    static int width, height;

    static void errorCallback(int errorCode, const char* description);

   public:
    Window(int width, int height, const char* name);
    ~Window();

    void swapBuffers() const;
    void pollEvents() const;
    bool shouldClose() const;

    GLFWwindow* getHandle() const;

    static int getWidth();
    static int getHeight();
};

#endif
