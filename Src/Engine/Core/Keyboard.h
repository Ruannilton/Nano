#ifndef NANO_KEYBOARD
#define NANO_KEYBOARD

#include "../graphic/GL.h"
#include "..//Utils.h"

GLFWwindow* window;
UNIQUE unsigned int keyboard[257];
#define NONE 3

#define Key(K) glfwGetKey(window, K) != GLFW_RELEASE
#define KeyPress(Key) keyboard[Key] == GLFW_PRESS+1
#define KeyRelease(Key) keyboard[Key] == GLFW_RELEASE+1
#define KeyHold(Key) keyboard[Key] == GLFW_REPEAT+1


void Keyboard_Clear();
void Keyboard_BindContext(GLFWwindow* win);
void Keyboard_Callback(GLFWwindow* win, int key, int scancode, int action, int mod);

#endif // !NANO_KEYBOARD


