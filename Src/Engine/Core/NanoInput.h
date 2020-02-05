#ifndef NANO_INPUT
#define NANO_INPUT

#include"Keyboard.h"
#include "Mouse.h"

__inline void ClearInputs() {
	KeyClear();
	MouseClear();
}


#endif // !NANO_INPUT


