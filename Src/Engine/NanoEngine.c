#include "NanoEngine.h"

int main(int argc, char* argv[]) {
	NanoApplication = Nano_Create();
	delta_time = 1;
	

	Nano_SetupOpenGL(NanoApplication);
	Renderer_Init();
	Setup();
	Start();
	Loader();
	printf("Press ESC to close\n");

	while (!glfwWindowShouldClose(NanoApplication->window))
	{
		glfwPollEvents();

		if (Input_KeyPress(GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(NanoApplication->window, 1);

		sprintf(NanoApplication->title, "FPS: %f", 1.0 / delta_time);
		glfwSetWindowTitle(NanoApplication->window, NanoApplication->title);

		TimeUpdate();
		Update();

		glClearColor(current_scene->BackGroundColor.R, current_scene->BackGroundColor.G, current_scene->BackGroundColor.B, current_scene->BackGroundColor.A);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Renderer_RenderScene();
		glfwSwapBuffers(NanoApplication->window);


		Input_Clear();
	}
	Cleanup();
	Nano_Delete(NanoApplication);

	return 0;
}