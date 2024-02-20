#pragma once

struct GLFWwindow;

class Window {
   private:
    GLFWwindow* handle;

    static void errorCallback(int errorCode, const char* description);

   public:
    Window(int width, int height, const char* name);
    ~Window();

    void swapBuffers() const;
    void pollEvents() const;
    bool shouldClose() const;

    inline GLFWwindow* getHandle() const {
        return handle;
    }
};
