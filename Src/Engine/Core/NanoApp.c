#include "NanoApp.h"

Nano* CreateNano() {
	if (!glfwInit()) {
		DEBUG("Error Glfw Init");
		return NULL;
	}

	Nano* nano = NEW(Nano);
	VERIFY(nano, NULL);
	

	nano->windowWidht = 800;
	nano->windowHeight = 640;
	nano->run = 1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	nano->window = glfwCreateWindow(800, 640, "Nano", NULL, NULL);

	glfwMakeContextCurrent(nano->window);
	if (glewInit() != GLEW_OK) DEBUG("Error Init Glew");


	return nano;
}

void DeleteNano(Nano* nano) {
	if (!nano) return;
	//glfwTerminate();
	free(nano);
}

