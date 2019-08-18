#include "Mouse.h"

void MouseScrollcallback(GLFWwindow* window, double xoffset, double yoffset)
{
}
void MouseButtonCallback(GLFWwindow* win, int button, int action, int mods) {
	mouseButtons[button] = action + 1;
	mouseButtonsHold[button] = action;
}
void MousePosCallback(GLFWwindow* win, double xpos, double ypos) {
	if (nano_mouse_first_flag == 0) {
		nano_mouse_first_flag = 1;
		mouse_Xpos = xpos;
		mouse_Ypos = ypos;
		return;
	}
	mouse_offsetX = xpos - mouse_Xpos;
	mouse_offsetY = mouse_Ypos - ypos;
	mouse_offsetX *= mouse_Sensitivity;
	mouse_offsetY *= mouse_Sensitivity;
	mouse_Xpos = xpos;
	mouse_Ypos = ypos;

}
