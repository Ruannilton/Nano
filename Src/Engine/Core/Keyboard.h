#pragma once

#include "../GL.h"

unsigned int keyboard[256];
#define NONE 3
#define KeyPress(Key) keyboard[Key] == GLFW_PRESS+1
#define KeyRelease(Key) keyboard[Key] == GLFW_RELEASE+1
#define KeyHold(Key) keyboard[Key] == GLFW_REPEAT+1

void KeyClear() {
	for (int i = 0; i < 256; i++) keyboard[i] = 0;
}
void keyCallback(GLFWwindow* win, int key, int scancode, int action, int mod) {
	keyboard[key] = action+1;
}


