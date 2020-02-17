#ifndef NANO_INPUT
#define NANO_INPUT

#include "../Utils.h"

#define Input_Key(K) glfwGetKey(input_context, K) != GLFW_RELEASE
#define Input_KeyPress(Key) input.keys[Key] == GLFW_PRESS+1
#define Input_KeyRelease(Key) input.keys[Key] == GLFW_RELEASE+1
#define Input_KeyHold(Key) input.keys[Key] == GLFW_REPEAT+1

#define Input_MousePress(BUTTON) mouseButtons[BUTTON] == GLFW_PRESS+1
#define Input_MouseHold(BUTTON) mouseButtonsHold[BUTTON] == GLFW_PRESS
#define Input_MouseRelease(BUTTON) mouseButtons[BUTTON] == GLFW_RELEASE+1

typedef struct {
	Vec2 position;
	Vec2 scroll;
	Vec2 delta;
	uint button_count;
	double sensitivity;
	short init;
}Mouse;

typedef struct {
	uint keys[GLFW_KEY_LAST + 1];
	Mouse mouse;
}Input;

UNIQUE int mouseButtons[GLFW_MOUSE_BUTTON_LAST + 1];
UNIQUE int mouseButtonsHold[GLFW_MOUSE_BUTTON_LAST + 1];
UNIQUE GLFWwindow* input_context;
UNIQUE Input input;

__inline void Input_Clear() {
	REPEAT_1(GLFW_KEY_LAST + 1) input.keys[i] = 0;
	REPEAT_1(GLFW_MOUSE_BUTTON_LAST + 1) mouseButtons[i] = 0;
	input.mouse.delta.x = 0;
	input.mouse.delta.y = 0;
	input.mouse.scroll.x = 0;
	input.mouse.scroll.y = 0;
}

__inline void Input_Init() {
	REPEAT_1(GLFW_MOUSE_BUTTON_LAST + 1) mouseButtons[i] = 0;
	REPEAT_1(GLFW_KEY_LAST + 1) input.keys[i] = 0;
}


void Input_SetMouse(uint button_count, double sensitivity);
void Input_BindContext(GLFWwindow* win);

Vec2 Input_GetMousePosition();
Vec2 Input_GetMouseDelta();
Vec2 Input_GetMouseScroll();
void Input_SetMouseSensitivity(double val);

void Keyboard_Callback(GLFWwindow* win, int key, int scancode, int action, int mod);
void Mouse_PosCallback(GLFWwindow* win, double xpos, double ypos);
void Mouse_ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void Mouse_ButtonCallback(GLFWwindow* win, int button, int action, int mods);

#endif // !NANO_INPUT


