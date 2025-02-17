#ifndef INPUT_HPP
#define INPUT_HPP

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class Input {
   public:
    enum class Key {
        A = GLFW_KEY_A,
        B = GLFW_KEY_B,
        C = GLFW_KEY_C,
        D = GLFW_KEY_D,
        E = GLFW_KEY_E,
        F = GLFW_KEY_F,
        G = GLFW_KEY_G,
        H = GLFW_KEY_H,
        I = GLFW_KEY_I,
        J = GLFW_KEY_J,
        K = GLFW_KEY_K,
        L = GLFW_KEY_L,
        M = GLFW_KEY_M,
        N = GLFW_KEY_N,
        O = GLFW_KEY_O,
        P = GLFW_KEY_P,
        Q = GLFW_KEY_Q,
        R = GLFW_KEY_R,
        S = GLFW_KEY_S,
        T = GLFW_KEY_T,
        U = GLFW_KEY_U,
        V = GLFW_KEY_V,
        W = GLFW_KEY_W,
        X = GLFW_KEY_X,
        Y = GLFW_KEY_Y,
        Z = GLFW_KEY_Z,
    };
    
    enum class KeyEventType { PRESSED, RELEASED };

    static void init(GLFWwindow* windowHandle);
    static void dispose();

    static bool isKeyPressed(Input::Key key);
    static bool isKeyReleased(Input::Key key);

    static void addKeyPressedCallback(void (*callback)(Input::Key, Input::KeyEventType));

   private:
    static GLFWwindow* windowHandle;
    static void (*keyCallback)(Input::Key, Input::KeyEventType);

    Input();
    ~Input();

    static void onKeyPressed(GLFWwindow* windowHandle, int key, int scancode, int action, int mods);
};

#endif
