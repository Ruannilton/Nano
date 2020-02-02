#ifndef NANO_ENGINE
#define NANO_ENGINE

#include "Utils.h"
#include "Core/NanoCore.h"
#include "Graphic/NanoRender.h"



UNIQUE Nano* NanoApplication;
UNIQUE float delta_time = 0;
UNIQUE double last_time = 0;
UNIQUE double current_time = 0;

extern void Start();
extern void Update();

__inline void MouseUpdate() {
	vec3 mouse_mov = { (float)mouse_delta_x, (float)mouse_delta_y, 0 };
	camera_Rotate(&currentCamera, mouse_mov);
	if (mouse_delta_scroll_y != 0) {
		camera_Zoom(&currentCamera, mouse_delta_scroll_y);

		DEBUG_C(ANSI_MAGENTA, "Camera FOV:  %f", currentCamera.fov);
	}
}

__inline void TimeUpdate() {
	current_time = glfwGetTime();
	delta_time = (float)(current_time - last_time);
	last_time = current_time;
}

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
	SetKeyWindow(NanoApplication->window);
	//stbi_set_flip_vertically_on_load(1);
	Start();

	printf("Press ESC to close\n");
	char* title = (char*)malloc(1);

	while (!glfwWindowShouldClose(NanoApplication->window))
	{
		TimeUpdate();
		sprintf(title, "FPS: %f", 1.0 / delta_time);
		glfwSetWindowTitle(NanoApplication->window,title);
		if (KeyPress(GLFW_KEY_ESCAPE)) glfwSetWindowShouldClose(NanoApplication->window, 1);
		ClearInputs();
		glfwPollEvents();
		glClearColor(BackGroundColor.R, BackGroundColor.G, BackGroundColor.B, BackGroundColor.A);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		MouseUpdate();
		Update();
		RenderScene();
		glfwSwapBuffers(NanoApplication->window);
		
		MouseRestore();
	}
	DeleteNano(NanoApplication);
	
	return 0;
}

#endif // !NANO_ENGINE



