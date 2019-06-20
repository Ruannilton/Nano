#include "NanoEngine.h"
#include <math.h>
float a = 0;

 void Start() {
	DEBUG("Start");
}

 void Update() {
	a+=0.0004f;
	chColor(cos(a), sin(a), 1-cos(a), 1, BackGroundColor);
	if (KeyPress(GLFW_KEY_A)) {
		DEBUG("KEY A PRESS");
	}
	if (MouseButtonPress(GLFW_MOUSE_BUTTON_1)) {
		DEBUG("MOUSE LEFT PRESS");
	}
}