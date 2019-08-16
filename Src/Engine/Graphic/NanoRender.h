#pragma once

#include "Color.h"
#include "Camera.h"
#include "../Core/NanoIO.h"
#include "../Components/RenderComponent.h"

Color BackGroundColor{ 0, 0.5f, 1, 1 };
Shader DefaultShader;
uint window_widht;
uint window_height;

RenderComponent* renders[256];
int index_renders = 0;

Camera currentCamera;


void initRenderSystem() {
	glViewport(0, 0, window_widht, window_height);
	vec3 pos = { 0,0,0 };
	camera_CreateCamera(&currentCamera, pos);
	camera_SetCameraPerspective(glm_rad(70.0f), ((float)window_widht) / window_height, 0.1f, 1000.0f, &currentCamera);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void AddRenderComponent(RenderComponent* cmp) {
	if (index_renders < 256) {
		renders[index_renders] = cmp;
		index_renders++;
	}

}

void RenderScene() {
	int i = 0;
	mat4 view;
	camera_ViewProjection(&currentCamera,&view);
	
	for (; i < index_renders; i++) {
		
		glUseProgram(renders[i]->mat->shader_id);
		glUniformMatrix4fv(7, 1, GL_FALSE, currentCamera.projection[0]);
		glUniformMatrix4fv(6, 1, GL_FALSE, view[0]);
		glUniformMatrix4fv(5, 1, GL_FALSE, *(renders[i]->transform));
		glBindVertexArray(renders[i]->Mesh_ID);		

		if(renders[i]->mat->fnc) renders[i]->mat->fnc(renders[i]->mat->shader_id,renders[i]->matData);
		
		glDrawElements(GL_TRIANGLES, renders[i]->IndexCount, GL_UNSIGNED_INT, 0);
		
	}
		
	
}

