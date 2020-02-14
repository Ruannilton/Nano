#include "NanoRender.h"




void Renderer_Init() {
	
	glViewport(0, 0, window_widht, window_height);
}

void Renderer_SetScene(Scene* scn) {
	current_scene = scn;
	current_camera = scn->camera_scene;
}



void RenderScene() {
	camera_UpdateView(current_scene->camera_scene);
	
	glUniformMatrix4fv(SHADER_PROJ_LOC, 1, GL_FALSE, (GLfloat*) current_camera->projection);
	glUniformMatrix4fv(SHADER_VIEW_LOC, 1, GL_FALSE, (GLfloat*) current_camera->view);
	
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

