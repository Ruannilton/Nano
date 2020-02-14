#include "Mouse.h"

void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	mouse_delta_scroll_x = xoffset;
	mouse_delta_scroll_y = yoffset;
}
void MouseButtonCallback(GLFWwindow* win, int button, int action, int mods) {
	mouseButtons[button] = action + 1;
	mouseButtonsHold[button] = action;
}

void MouseUpdate() {
	
}


void MousePosCallback(GLFWwindow* win, double xpos, double ypos) {
	if (nano_mouse_first_flag == 0) {
		nano_mouse_first_flag = 1;
		mouse_Xpos = xpos;
		mouse_Ypos = ypos;
		return;
	}
	mouse_delta_x = xpos - mouse_Xpos;
	mouse_delta_y = mouse_Ypos - ypos;
	mouse_delta_x *= mouse_Sensitivity;
	mouse_delta_y *= mouse_Sensitivity;
	mouse_Xpos = xpos;
	mouse_Ypos = ypos;

}


