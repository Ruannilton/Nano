#include "NanoEngine.h"

int main(int argc, char* argv[]) {
	delta_time = 1;
	unsigned int avg_fps = 0;
	unsigned int tot = 0;
	unsigned long long int count = 1;
	
	
	Nano_Create();
	Setup();
	Nano_CreateWindow();
	Nano_SetupOpenGL();
	Show_Info();
	Renderer_Init();
	Start();
	Loader();
	printf("Press ESC to close\n");

	while (!glfwWindowShouldClose(nano->window))
	{
		glfwPollEvents();

		if (Input_KeyPress(GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(nano->window, 1);
		float fps = 1.0 / delta_time;
		tot += (int)fps;
		sprintf(nano->title, "FPS: %f  AVG: %u MULTISAMPLING: %d", fps, tot/count,nano->multisamples_level );
		glfwSetWindowTitle(nano->window, nano->title);

		TimeUpdate();
		Update();

		glClearColor(current_scene->BackGroundColor.R, current_scene->BackGroundColor.G, current_scene->BackGroundColor.B, current_scene->BackGroundColor.A);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Renderer_RenderScene();
		glfwSwapBuffers(nano->window);

		Input_Clear();
		count++;
	}
	Cleanup();
	Nano_Delete(nano);

	return 0;
}