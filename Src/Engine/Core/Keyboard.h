#ifndef NANO_KEYBOARD
#define NANO_KEYBOARD

#include "../graphic/GL.h"
#include "..//Utils.h"

UNIQUE unsigned int keyboard[256];
#define NONE 3
#define KeyPress(Key) keyboard[Key] == GLFW_PRESS+1
#define KeyRelease(Key) keyboard[Key] == GLFW_RELEASE+1
#define KeyHold(Key) keyboard[Key] == GLFW_REPEAT+1

void KeyClear();
void keyCallback(GLFWwindow* win, int key, int scancode, int action, int mod);

#endif // !NANO_KEYBOARD


