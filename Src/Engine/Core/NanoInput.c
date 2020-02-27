#include "NanoInput.h"

void Input_SetMouse(uint button_count, double sensitivity) {
	input.mouse.button_count = button_count;
	input.mouse.sensitivity = sensitivity;
}

void Mouse_ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	input.mouse.delta = (Vec2){ xoffset ,yoffset };
}
void Mouse_ButtonCallback(GLFWwindow* win, int button, int action, int mods) {
	mouseButtons[button] = action + 1;
	mouseButtonsHold[button] = action;
}

void Mouse_PosCallback(GLFWwindow* win, double xpos, double ypos) {
	if (input.mouse.init == 0) {
		input.mouse.init = 1;
		input.mouse.position = (Vec2){ xpos ,ypos };
		return;
	}

	input.mouse.delta = (Vec2){ xpos - input.mouse.position.x ,input.mouse.position.y - ypos };
	input.mouse.position = (Vec2){ xpos ,ypos };
	Vec2Mul(input.mouse.delta, input.mouse.sensitivity);
}

Vec2 Input_GetMousePosition() {
	return input.mouse.position;
}

Vec2 Input_GetMouseDelta() {
	return input.mouse.delta;
}

Vec2 Input_GetMouseScroll() {
	return input.mouse.scroll;
}

void Input_SetMouseSensitivity(double val) {
	input.mouse.sensitivity = val;
}

void Input_BindContext(GLFWwindow* win) {
	input_context = win;
}

void Keyboard_Callback(GLFWwindow* win, int key, int scancode, int action, int mod) {
	input.keys[key] = action + 1;
}