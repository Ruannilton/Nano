#include "NanoRender.h"

UNIQUE RenderComponent* render_list[128];
UNIQUE int render_list_count = 0;

void initRenderSystem() {
	vec3 pos = { 0,0,0.5f };

	BackGroundColor[0] = 0;
	BackGroundColor[1] = 0.5f;
	BackGroundColor[2] = 1;
	BackGroundColor[3] = 1;

	glViewport(0, 0, window_widht, window_height);
    DefaultShader = shader_CreateShader(ReadFile("Assets/Shaders/default.vs"), ReadFile("Assets/Shaders/default.fs"));
	camera_CreateCamera(&currentCamera, pos);
	camera_SetCameraPerspective(glm_rad(70.0f), ((float)window_widht) / window_height, 0.1f, 1000.0f, &currentCamera);
}

void AddToRender(RenderComponent* c) {
	if (render_list_count < 128) {
		render_list[render_list_count] = c;
		render_list_count++;
	 }
	
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


void RenderScene() {
	camera_UpdateView(&currentCamera);
	
	register int i = 0;
	
	for (; i < render_list_count; i++) {
		
		if (render_list[i]->mat == NULL) glUseProgram(DefaultShader);
		else glUseProgram(render_list[i]->mat->shader_id);

	
		glUniformMatrix4fv(SHADER_PROJ_LOC, 1, GL_FALSE, currentCamera.projection);
	    glUniformMatrix4fv(SHADER_VIEW_LOC, 1, GL_FALSE, currentCamera.view);
        glUniformMatrix4fv(SHADER_MODEL_LOC, 1, GL_FALSE, render_list[i]->transform);
		
		render_list[i]->mat->fnc(render_list[i]->mat->shader_id, render_list[i]->mat->data);
		glBindVertexArray(render_list[i]->mesh->mesh_id);
		glDrawElements(GL_TRIANGLES, render_list[i]->mesh->index_count, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}

