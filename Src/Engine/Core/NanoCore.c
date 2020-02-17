#include "NanoCore.h"

Nano* Nano_Create() {
	if (!glfwInit()) {
		DEBUG("Error Glfw Init");
		return NULL;
	}

	Nano* nano = NEW(Nano);
	VERIFY(nano, NULL);


	nano->windowWidht = 800;
	nano->windowHeight = 640;
	nano->run = 1;
	nano->title = (char*)malloc(sizeof(char) * 12);
	nano->progam_path = (char*)malloc(sizeof(char) * FILENAME_MAX);

	GetCurrentDir(nano->progam_path, sizeof(char) * FILENAME_MAX);
	DEBUG("Program path: %s",nano->progam_path);

	strcpy(nano->title, "Nano Engine");
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwSwapInterval(1);

	nano->window = glfwCreateWindow(800, 640, nano->title, NULL, NULL);

	glfwMakeContextCurrent(nano->window);
	if (glewInit() != GLEW_OK) DEBUG("Error Init Glew");


	return nano;
}

void Nano_Delete(Nano* nano) {
	if (!nano) return;
	//glfwTerminate();
	free(nano);
}

void TimeUpdate() {
	current_time = glfwGetTime();
	delta_time = (float)(current_time - last_time);
	last_time = current_time;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	//camera_SetCameraPerspective(currentCamera->fov, ((float)width) / height, currentCamera->zNear, currentCamera->zFar, &currentCamera);
}

void Nano_SetupOpenGL(Nano* NanoApplication) {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSetInputMode(NanoApplication->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetKeyCallback(NanoApplication->window, Keyboard_Callback);
	glfwSetCursorPosCallback(NanoApplication->window, Mouse_PosCallback);
	glfwSetScrollCallback(NanoApplication->window, Mouse_ScrollCallback);
	glfwSetMouseButtonCallback(NanoApplication->window, Mouse_ButtonCallback);
	glfwSetFramebufferSizeCallback(NanoApplication->window, framebufferSizeCallback);
	Input_BindContext(NanoApplication->window);
}

