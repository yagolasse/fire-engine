#pragma once

class Window {
   private:
    GLFWwindow* handle;

    static void errorCallback(int errorCode, const char* description);

   public:
    Window(int width, int height, const char* name);
    ~Window();

    inline GLFWwindow* getHandle() const {
        return handle;
    }

    void swapBuffers() const;
    void pollEvents() const;
    bool shouldClose() const;
};
