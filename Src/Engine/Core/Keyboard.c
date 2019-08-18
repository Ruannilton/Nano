#include "Keyboard.h"

void KeyClear() {
	for (int i = 0; i < 256; i++) keyboard[i] = 0;
}
void keyCallback(GLFWwindow* win, int key, int scancode, int action, int mod) {
	keyboard[key] = action + 1;
}
