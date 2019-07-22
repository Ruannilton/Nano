#ifndef NANO_ENGINE
#define NANO_ENGINE

#include "Core/NanoApp.h"
#include "Core/NanoIO.h"
#include "Core/NanoInput.h"

#include "Graphic/NanoRender.h"
#include "Graphic/Mesh.h"
#include "Graphic/Texture.h"

mat4 MAT4_IDENTITY = GLM_MAT4_IDENTITY_INIT;
Nano* NanoApplication;

void Start();
void Update();

int main() {
	NanoApplication = CreateNano();
	
	glfwSetInputMode(NanoApplication->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetKeyCallback(NanoApplication->window, keyCallback);
	glfwSetCursorPosCallback(NanoApplication->window, MousePosCallback);
	glfwSetMouseButtonCallback(NanoApplication->window, MouseButtonCallback);
	glfwSetFramebufferSizeCallback(NanoApplication->window, framebufferSizeCallback);

	DefaultShader = shader_CreateShader(ReadFile("Src/Shaders/default.vs"), ReadFile("Src/Shaders/default.fs"));

	window_height = NanoApplication->windowHeight;
	window_widht = NanoApplication->windowWidht;
	initMouse(NanoApplication);
	initRenderSystem();

	stbi_set_flip_vertically_on_load(1);

	Start();
	printf("Press ESC to close\n");
	while (!glfwWindowShouldClose(NanoApplication->window))
	{	
		if (KeyPress(GLFW_KEY_ESCAPE)) glfwSetWindowShouldClose(NanoApplication->window, 1);
		ClearInputs();
		glfwPollEvents();
		glClearColor(BackGroundColor[C_RED], BackGroundColor[C_GREEN], BackGroundColor[C_BLUE], BackGroundColor[C_ALPHA]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
		Update();
		RenderScene();
		glfwSwapBuffers(NanoApplication->window);		
		mouse_offsetX = 0;
		mouse_offsetY = 0;
	}
	glfwTerminate();
	free(NanoApplication);
	return 0;
}
#endif // ! NANO_ENGINE

