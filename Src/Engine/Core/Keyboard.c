#include "Keyboard.h"

void Keyboard_BindContext(GLFWwindow* win) {
	window = win;
}
void Keyboard_Clear() {
	for (int i = 0; i < 256; i++) keyboard[i] = 0;
}
void Keyboard_Callback(GLFWwindow* win, int key, int scancode, int action, int mod) {
	keyboard[key] = action + 1;
}
