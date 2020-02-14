#include "NanoEngine.h"

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

void SetupOpenGL(Nano* NanoApplication) {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSetInputMode(NanoApplication->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetKeyCallback(NanoApplication->window, keyCallback);
	glfwSetCursorPosCallback(NanoApplication->window, MousePosCallback);
	glfwSetScrollCallback(NanoApplication->window, MouseScrollCallback);
	glfwSetMouseButtonCallback(NanoApplication->window, MouseButtonCallback);
	glfwSetFramebufferSizeCallback(NanoApplication->window, framebufferSizeCallback);
	BindKeyboardContext(NanoApplication->window);
}

int main() {
	NanoApplication = CreateNano();
	delta_time = 1;
	window_height = NanoApplication->windowHeight;
	window_widht = NanoApplication->windowWidht;

	SetupOpenGL(NanoApplication);
	Renderer_Init();
	Start();

	printf("Press ESC to close\n");
	
	while (!glfwWindowShouldClose(NanoApplication->window))
	{
		if (KeyPress(GLFW_KEY_ESCAPE)) glfwSetWindowShouldClose(NanoApplication->window, 1);

		sprintf(NanoApplication->title, "FPS: %f", 1.0 / delta_time);
		glfwSetWindowTitle(NanoApplication->window, NanoApplication->title);

		glfwPollEvents();
		
		TimeUpdate();
		Update();

		glClearColor(current_scene->BackGroundColor.R, current_scene->BackGroundColor.G, current_scene->BackGroundColor.B, current_scene->BackGroundColor.A);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		RenderScene();
		glfwSwapBuffers(NanoApplication->window);
		
	
		ClearInputs();
	}
	DeleteNano(NanoApplication);

	return 0;
}