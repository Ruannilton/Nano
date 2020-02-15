#ifndef NANO_MOUSE
#define NANO_MOUSE

#include "../Graphic/GL.h"
#include "../Utils.h"
#include "NanoApp.h"

#define MouseButtonPress(BUTTON) mouseButtons[BUTTON] == GLFW_PRESS+1
#define MouseButtonHold(BUTTON) mouseButtonsHold[BUTTON] == GLFW_PRESS
#define MouseButtonRelease(BUTTON) mouseButtons[BUTTON] == GLFW_RELEASE+1

typedef struct {
	Vec2 position;
	Vec2 scroll;
	Vec2 delta;
	double sensitivity;
}Mouse;

UNIQUE double mouse_Xpos, mouse_Ypos, mouse_delta_x = 0, mouse_delta_y = 0, mouse_Sensitivity = 0.05f, mouse_delta_scroll_x=0, mouse_delta_scroll_y=0;
UNIQUE int mouseButtons[GLFW_MOUSE_BUTTON_LAST + 1];
UNIQUE int mouseButtonsHold[GLFW_MOUSE_BUTTON_LAST + 1];
UNIQUE int nano_mouse_first_flag = 0;


__inline void Mouse_Init(Nano* nanoApp) {
	REPEAT_1(GLFW_MOUSE_BUTTON_LAST + 1) mouseButtons[i] = 0;
}

__inline void Mouse_Clear() {
		mouse_delta_x = 0;
		mouse_delta_y = 0;
		mouse_delta_scroll_x = 0;
		mouse_delta_scroll_y = 0;
		REPEAT_1(GLFW_MOUSE_BUTTON_LAST + 1) mouseButtons[i] = 0;
}

void Mouse_Update();
void Mouse_PosCallback(GLFWwindow* win, double xpos, double ypos);
void Mouse_ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void Mouse_ButtonCallback(GLFWwindow* win, int button, int action, int mods);



#endif // !NANO_MOUSE













