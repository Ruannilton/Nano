#include "NanoRender.h"


void initRenderSystem() {
	vec3 pos = { 0,0,0 };

	BackGroundColor[0] = 0;
	BackGroundColor[1] = 0.5f;
	BackGroundColor[2] = 1;
	BackGroundColor[3] = 1;

	glViewport(0, 0, window_widht, window_height);
    DefaultShader = shader_CreateShader(ReadFile("Assets/Shaders/default.vs"), ReadFile("Assets/Shaders/default.fs"));
	camera_CreateCamera(&currentCamera, pos);
	camera_SetCameraPerspective(glm_rad(70.0f), ((float)window_widht) / window_height, 0.1f, 1000.0f, &currentCamera);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


void RenderScene() {

}

