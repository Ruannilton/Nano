#include "NanoRender.h"


UNIQUE RenderComponent* render_list[128];
UNIQUE int render_list_count = 0;

void initRenderSystem() {
	vec3 pos = { 0,0,10.0f };

	BackGroundColor[0] = 0;
	BackGroundColor[1] = 0.5f;
	BackGroundColor[2] = 1;
	BackGroundColor[3] = 1;

	glViewport(0, 0, window_widht, window_height);
    DefaultShader = shader_CreateShader(ReadFile("Assets/Shaders/default.vert"), ReadFile("Assets/Shaders/default.frag"));
	camera_CreateCamera(&currentCamera, pos);
	camera_SetCameraPerspective(currentCamera.fov, ((float)window_widht) / window_height, 0.1f, 1000.0f, &currentCamera);
}

void AddToRender(RenderComponent* c) {
	if (render_list_count < 128) {
		render_list[render_list_count] = c;
		render_list_count++;
	 }
	DEBUG("CCOMP COUNT: %d", render_list_count);
	
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	camera_SetCameraPerspective(currentCamera.fov, ((float)width) / height, currentCamera.zNear, currentCamera.zFar, &currentCamera);
}


void RenderScene() {
	camera_UpdateView(&currentCamera);
	
	glUniformMatrix4fv(SHADER_PROJ_LOC, 1, GL_FALSE, currentCamera.projection);
	glUniformMatrix4fv(SHADER_VIEW_LOC, 1, GL_FALSE, currentCamera.view);
	
	register int i = 0;
	Material* cMat;
	for (; i < render_list_count; i++) {
		cMat = render_list[i]->mat;

		if (cMat == NULL) glUseProgram(DefaultShader);
		else glUseProgram(cMat->shader_id);
		cMat->fnc(cMat->shader_id, cMat->data);

        glUniformMatrix4fv(SHADER_MODEL_LOC, 1, GL_FALSE, render_list[i]->transform);
		glBindVertexArray(render_list[i]->mesh->mesh_id);
		glDrawElements(GL_TRIANGLES, render_list[i]->mesh->index_count, GL_UNSIGNED_INT, 0);
	}
		glBindVertexArray(0);
}

