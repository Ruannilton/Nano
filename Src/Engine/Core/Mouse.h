#ifndef NANO_MOUSE
#define NANO_MOUSE

#include "../GL.h"
#include "../Utils.h"

int mouseButtons[GLFW_MOUSE_BUTTON_LAST + 1];
int mouseButtonsHold[GLFW_MOUSE_BUTTON_LAST + 1];


#define MouseButtonPress(BUTTON) mouseButtons[BUTTON] == GLFW_PRESS+1
#define MouseButtonHold(BUTTON) mouseButtonsHold[BUTTON] == GLFW_PRESS
#define MouseButtonRelease(BUTTON) mouseButtons[BUTTON] == GLFW_RELEASE+1

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

}

#endif // !NANO_MOUSE
