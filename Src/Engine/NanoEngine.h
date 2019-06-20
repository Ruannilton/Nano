#ifndef NANO_ENGINE
#define NANO_ENGINE

#include "Core/NanoApp.h"
#include "Core/NanoIO.h"
#include "Core/NanoInput.h"
#include "Graphic/RenderEngine.h"


Nano* NanoApplication;


 void Start();
 void Update();

int main() {
	NanoApplication = CreateNano();
	
	glfwSetKeyCallback(NanoApplication->window, keyCallback);
	glfwSetCursorPosCallback(NanoApplication->window, MousePosCallback);
	glfwSetMouseButtonCallback(NanoApplication->window, MouseButtonCallback);

	DefaultShader = CreateShader(ReadFile("Src/default.vs"), ReadFile("Src/default.fs"));

	window_height = NanoApplication->windowHeight;
	window_widht = NanoApplication->windowWidht;

	Start();
	
	while (!glfwWindowShouldClose(NanoApplication->window))
	{		
		ClearInputs();
		glfwPollEvents();
		glClearColor(BackGroundColor[C_RED], BackGroundColor[C_GREEN], BackGroundColor[C_BLUE], BackGroundColor[C_ALPHA]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
		Update();
		glfwSwapBuffers(NanoApplication->window);	
		
	}

	free(NanoApplication);
	return 0;
}
#endif // ! NANO_ENGINE

