#include "NanoRender.h"

void Renderer_Init() {
	
	glViewport(0, 0, NanoApplication->windowWidht, NanoApplication->windowHeight);
	glGenBuffers(1, &matrix_buffer);
	glBindBuffer(GL_UNIFORM_BUFFER, matrix_buffer);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(mat4), 0, GL_STATIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER, SHADER_UNIFORM_MATRIX_LOC, matrix_buffer, 0, 2 * sizeof(mat4));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glGenBuffers(1, &lights_buffer);
	glBindBuffer(GL_UNIFORM_BUFFER, lights_buffer);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(int) + sizeof(DirectionalLight) + 128 * sizeof(SpotLight) + 128 * sizeof(PointLight), 0, GL_STATIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, SHADER_UNIFORM_LIGHT_LOC, matrix_buffer);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Renderer_SetupProjection() {
	if (current_camera != NULL) {
		glBindBuffer(GL_UNIFORM_BUFFER, matrix_buffer);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(mat4), current_camera->projection);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}

void Renderer_SetupLighting() {
	glBindBuffer(GL_UNIFORM_BUFFER, lights_buffer);
	Vec2 lights_count = { current_scene->point_lights.count,current_scene->spot_lights.count};
	glBufferSubData(GL_UNIFORM_BUFFER, 0, 2*sizeof(int), lights_count.arr);
	glBufferSubData(GL_UNIFORM_BUFFER, 16, 4 * sizeof(vec3), &(current_scene->sun));
	glBufferSubData(GL_UNIFORM_BUFFER, 80,    (size_t)lights_count.x * sizeof(PointLight), current_scene->point_lights.buffer);
	glBufferSubData(GL_UNIFORM_BUFFER, 10320, (size_t)lights_count.y * sizeof(SpotLight) , current_scene->spot_lights.buffer);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}


void Renderer_SetScene(Scene* scn) {
	current_scene = scn;
	current_camera = scn->camera_scene;
	Renderer_SetupProjection();
}

void Renderer_RenderScene() {
	Camera_UpdateView(current_camera);
	
	
	glBindBuffer(GL_UNIFORM_BUFFER, matrix_buffer);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(mat4), current_camera->projection);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(mat4), sizeof(mat4), current_camera->view);
	glBindBufferRange(GL_UNIFORM_BUFFER, SHADER_UNIFORM_MATRIX_LOC, matrix_buffer, 0, 2 * sizeof(mat4));
	glUseProgram(1);
	//glBindBuffer(GL_UNIFORM_BUFFER, 0);
	

	//Renderer_SetupLighting();
	RenderData* rd = Dictionary_Get(RenderData, &(current_scene->render_data), 1);
	InstanceList* il = Dictionary_Get(InstanceList, &rd->renderer_lists, 1);
	Instance* instance = Vector_Get(Instance, &il->instances, 0);
	
	
	glBindVertexArray(1);
	glUniformMatrix4fv(SHADER_MODEL_LOC, 1, GL_FALSE, (GLfloat*) instance->transform);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	/*register uint i = 0;
	Material* cMat;

	for (; i < render_list_count; i++) {
		cMat = render_list[i]->mat;

		if (cMat != NULL) {
			glUseProgram(cMat->shader_id);
			cMat->fnc(cMat->shader_id, cMat->data);
		}
		else {
			glUseProgram(DefaultShader);
		}
		
        glUniformMatrix4fv(SHADER_MODEL_LOC, 1, GL_FALSE,(GLfloat*) render_list[i]->transform);
		glBindVertexArray(render_list[i]->mesh->mesh_id);
		glDrawElements(GL_TRIANGLES, render_list[i]->mesh->index_count, GL_UNSIGNED_INT, 0);
	
	}*/
	
	glBindVertexArray(0);
}

