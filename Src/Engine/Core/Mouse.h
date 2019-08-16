#pragma once

#include "../GL.h"
#include "../Utils.h"

float mouse_Xpos, mouse_Ypos,mouse_offsetX,mouse_offsetY,mouse_Sensitivity = 0.05f;
int mouseButtons[GLFW_MOUSE_BUTTON_LAST + 1];
int mouseButtonsHold[GLFW_MOUSE_BUTTON_LAST + 1];
int first = 0;

#define MouseButtonPress(BUTTON) mouseButtons[BUTTON] == GLFW_PRESS+1
#define MouseButtonHold(BUTTON) mouseButtonsHold[BUTTON] == GLFW_PRESS
#define MouseButtonRelease(BUTTON) mouseButtons[BUTTON] == GLFW_RELEASE+1

__inline void initMouse(Nano* nanoApp) {
	mouse_offsetX = nanoApp->windowWidht / 2.0f;
	mouse_offsetY = nanoApp->windowHeight / 2.0f;
}

void MouseClear() {
	REPEAT(GLFW_MOUSE_BUTTON_LAST+1) mouseButtons[i] = 0;
}

void MouseScrollcallback(GLFWwindow* window, double xoffset, double yoffset)
{
}
void MouseButtonCallback(GLFWwindow* win, int button, int action, int mods) {
	mouseButtons[button] = action + 1;
	mouseButtonsHold[button] = action;
}
void MousePosCallback(GLFWwindow* win,double xpos,double ypos) {
	if (first == 0) {
		first = 1;
		mouse_Xpos = xpos;
		mouse_Ypos = ypos;
		return;
	}
	mouse_offsetX = xpos-mouse_Xpos;
	mouse_offsetY = mouse_Ypos - ypos;
	mouse_offsetX *= mouse_Sensitivity;
	mouse_offsetY *= mouse_Sensitivity;
	mouse_Xpos = xpos;
	mouse_Ypos = ypos;
	
}


