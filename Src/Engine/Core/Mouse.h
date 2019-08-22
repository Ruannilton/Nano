#ifndef NANO_MOUSE
#define NANO_MOUSE

#include "../Graphic/GL.h"
#include "../Utils.h"
#include "NanoApp.h"

UNIQUE float mouse_Xpos, mouse_Ypos, mouse_offsetX, mouse_offsetY, mouse_Sensitivity = 0.05f;
UNIQUE int mouseButtons[GLFW_MOUSE_BUTTON_LAST + 1];
UNIQUE int mouseButtonsHold[GLFW_MOUSE_BUTTON_LAST + 1];
UNIQUE int nano_mouse_first_flag = 0;

#define MouseButtonPress(BUTTON) mouseButtons[BUTTON] == GLFW_PRESS+1
#define MouseButtonHold(BUTTON) mouseButtonsHold[BUTTON] == GLFW_PRESS
#define MouseButtonRelease(BUTTON) mouseButtons[BUTTON] == GLFW_RELEASE+1

__inline void initMouse(Nano* nanoApp) {
	mouse_offsetX = nanoApp->windowWidht / 2.0f;
	mouse_offsetY = nanoApp->windowHeight / 2.0f;
}

__inline void MouseClear() {
	REPEAT(i,GLFW_MOUSE_BUTTON_LAST + 1,1) mouseButtons[i] = 0;
}

void MousePosCallback(GLFWwindow* win, double xpos, double ypos);
void MouseScrollcallback(GLFWwindow* window, double xoffset, double yoffset);
void MouseButtonCallback(GLFWwindow* win, int button, int action, int mods);
void MousePosCallback(GLFWwindow* win, double xpos, double ypos);


#endif // !NANO_MOUSE













