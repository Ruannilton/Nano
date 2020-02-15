#ifndef NANO_INPUT
#define NANO_INPUT

#include"Keyboard.h"
#include "Mouse.h"

__inline void Input_Clear() {
	Keyboard_Clear();
	Mouse_Clear();
}


#endif // !NANO_INPUT


