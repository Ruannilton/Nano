#ifndef NANO_ENGINE
#define NANO_ENGINE

#include "Utils.h"
#include "Core/NanoCore.h"
#include "Graphic/NanoRender.h"
#include <STB/stb_image.h>


UNIQUE Nano* NanoApplication;
UNIQUE float delta_time = 0;
UNIQUE double last_time = 0;
UNIQUE double current_time = 0;

void Start();
void Update();

int main() {
	NanoApplication = CreateNano();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
	glfwSetInputMode(NanoApplication->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetKeyCallback(NanoApplication->window, keyCallback);
	glfwSetCursorPosCallback(NanoApplication->window, MousePosCallback);
	glfwSetScrollCallback(NanoApplication->window, MouseScrollCallback);
	glfwSetMouseButtonCallback(NanoApplication->window, MouseButtonCallback);
	glfwSetFramebufferSizeCallback(NanoApplication->window, framebufferSizeCallback);

	window_height = NanoApplication->windowHeight;
	window_widht = NanoApplication->windowWidht;

	initRenderSystem();
	stbi_set_flip_vertically_on_load(1);
	Start();

	printf("Press ESC to close\n");
	while (!glfwWindowShouldClose(NanoApplication->window))
	{
		current_time = glfwGetTime();
		delta_time = (float)(current_time - last_time);
		last_time = current_time;

		if (KeyPress(GLFW_KEY_ESCAPE)) glfwSetWindowShouldClose(NanoApplication->window, 1);
		ClearInputs();
		glfwPollEvents();
		glClearColor(BackGroundColor[C_RED], BackGroundColor[C_GREEN], BackGroundColor[C_BLUE], BackGroundColor[C_ALPHA]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Update();
		RenderScene();
		glfwSwapBuffers(NanoApplication->window);
		
		MouseRestore();
	}
	DeleteNano(NanoApplication);
	
	return 0;
}

#endif // !NANO_ENGINE



