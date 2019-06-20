#ifndef NANO_APP
#define NANO_APP

#include "../GL.h"
#include "../Utils.h"
#include <stdio.h>

typedef struct {
	GLFWwindow* window;
	unsigned int windowWidht, windowHeight;
	unsigned int run;
}Nano;

Nano* CreateNano() {
	if (!glfwInit()) {
		DEBUG("Error Glfw Init");
		return NULL;
	}

	Nano* nano = NEW(Nano);
	if (!nano) DEBUG("Error Nano Alloc");

	nano->windowWidht  = 800;
	nano->windowHeight = 640;
	nano->run = 1;
	
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	nano->window= glfwCreateWindow(800, 649, "Nano", NULL, NULL);
	
	glfwMakeContextCurrent(nano->window);
	if (glewInit() != GLEW_OK) DEBUG("Error Init Glew");
	
	
	return nano;
}
#endif // !NANO_APP

