#ifndef NANO_APP
#define NANO_APP

#include "../Graphic/GL.h"
#include "../Utils.h"
#include <stdio.h>

typedef struct {
	GLFWwindow* window;
	char* title;
	unsigned int windowWidht, windowHeight;
	unsigned int run;
}Nano;

Nano* CreateNano();
void DeleteNano(Nano* nano);
#endif // !NANO_APP





