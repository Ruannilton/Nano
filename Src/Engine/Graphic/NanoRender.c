#include "NanoRender.h"

#define MAT_SIZE (2 * sizeof(mat4))
#define LIGHT_SIZE (sizeof(vec4) + 5*(sizeof(vec4)) + 256*128)
#define MODEL_SIZE (1024*sizeof(mat4))

void Renderer_Init() {

	glGenBuffers(1, &matrix_buffer);
	glBindBuffer(GL_UNIFORM_BUFFER, matrix_buffer);
	glBufferData(GL_UNIFORM_BUFFER, MAT_SIZE, 0, GL_DYNAMIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER, SHADER_UNIFORM_MATRIX_LOC, matrix_buffer, 0, MAT_SIZE);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glGenBuffers(1, &lights_buffer);
	glBindBuffer(GL_UNIFORM_BUFFER, lights_buffer);
	glBufferData(GL_UNIFORM_BUFFER, LIGHT_SIZE, NULL, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, SHADER_UNIFORM_LIGHT_LOC, lights_buffer);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	
	glGenBuffers(1, &model_buffer);
	/*glGenBuffers(1, &models_buffer);
	glBindBuffer(GL_UNIFORM_BUFFER, models_buffer);
	glBufferData(GL_UNIFORM_BUFFER, MODEL_SIZE, NULL, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, SHADER_UNIFORM_MODEL_LOC, models_buffer);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);*/
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
	float counts[2] = {current_scene->point_lights.count,current_scene->spot_lights.count};
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(vec2), counts);                            
	glBufferSubData(GL_UNIFORM_BUFFER, 16, sizeof(vec3), current_scene->sun.Ambient.arr);   
	glBufferSubData(GL_UNIFORM_BUFFER, 32, sizeof(vec3), current_scene->sun.Diffuse.arr);   
	glBufferSubData(GL_UNIFORM_BUFFER, 48, sizeof(vec3), current_scene->sun.Specular.arr);  
	glBufferSubData(GL_UNIFORM_BUFFER, 64, sizeof(vec3), current_scene->sun.Direction.arr); 
	glBufferSubData(GL_UNIFORM_BUFFER, 80, sizeof(vec3), current_scene->sun.Color.arr);

	float attenuation[3] = {0,0,0};
	float cuttOff[2] = { 0,0 };

	size_t index = 96;
	Vec_Iterator light_iter = Vec_Iterator_Get(&current_scene->point_lights);
	for (; Vec_Iterator_Next(&light_iter); index += 128) {

		PointLight* pl = light_iter.data;
		attenuation[0] = pl->Constant;
		attenuation[1] = pl->Linear;
		attenuation[2] = pl->Quadratic;

		glBufferSubData(GL_UNIFORM_BUFFER, index, sizeof(vec3), pl->Ambient.arr);    
		glBufferSubData(GL_UNIFORM_BUFFER, index + 16, sizeof(vec3), pl->Diffuse.arr);  
		glBufferSubData(GL_UNIFORM_BUFFER, index + 32, sizeof(vec3), pl->Specular.arr); 
		glBufferSubData(GL_UNIFORM_BUFFER, index + 48, sizeof(vec3), pl->Position.arr); 
		glBufferSubData(GL_UNIFORM_BUFFER, index + 64, sizeof(vec3), attenuation);
		glBufferSubData(GL_UNIFORM_BUFFER, index + 80, sizeof(vec3), pl->Color.arr);
	}

	light_iter = Vec_Iterator_Get(&current_scene->spot_lights);
	for (; Vec_Iterator_Next(&light_iter); index += 128) {

		SpotLight* sl = light_iter.data;
		
		attenuation[0] = sl->Constant;
		attenuation[1] = sl->Linear;
		attenuation[2] = sl->Quadratic;
		cuttOff[0] = sl->cutOff;
		cuttOff[1] = sl->outerCutOff;

		glBufferSubData(GL_UNIFORM_BUFFER, index, sizeof(vec3), sl->Ambient.arr);    
		glBufferSubData(GL_UNIFORM_BUFFER, index + 16, sizeof(vec3), sl->Diffuse.arr);  
		glBufferSubData(GL_UNIFORM_BUFFER, index + 32, sizeof(vec3), sl->Specular.arr); 
		glBufferSubData(GL_UNIFORM_BUFFER, index + 48, sizeof(vec3), sl->Position.arr); 
		glBufferSubData(GL_UNIFORM_BUFFER, index + 64, sizeof(vec3), attenuation); 
		glBufferSubData(GL_UNIFORM_BUFFER, index + 80, sizeof(vec3), sl->Color.arr);
		glBufferSubData(GL_UNIFORM_BUFFER, index + 96, sizeof(vec3), sl->Direction.arr);
		glBufferSubData(GL_UNIFORM_BUFFER, index + 112, sizeof(vec2), cuttOff);
	}

	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}


void Renderer_SetScene(Scene* scn) {
	current_scene = scn;
	current_camera = scn->camera_scene;
	Renderer_SetupProjection();
}

void SetModels(uint count, mat4* models) {
	glBindBuffer(GL_ARRAY_BUFFER, model_buffer);
	glBufferData(GL_ARRAY_BUFFER, count*sizeof(mat4), models, GL_STATIC_DRAW);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)0);
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)sizeof(vec4));
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(2 * sizeof(vec4)));
	glEnableVertexAttribArray(7);
	glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(3 * sizeof(vec4)));

	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);
	glVertexAttribDivisor(7, 1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderer_RenderScene() {
	Camera_UpdateView(current_camera);

	glBindBuffer(GL_UNIFORM_BUFFER, matrix_buffer);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(mat4), current_camera->projection);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(mat4), sizeof(mat4), current_camera->view);
	glBindBufferRange(GL_UNIFORM_BUFFER, SHADER_UNIFORM_MATRIX_LOC, matrix_buffer, 0, 2 * sizeof(mat4));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	
	
	Renderer_SetupLighting();

	Skybox_Use(&current_scene->sky);

	Dic_Iterator rd_iter = Dic_Iterator_Get(&(current_scene->render_data));
	Dic_Iterator dic_iter;
	Vec_Iterator vec_iter;

	
	

	while (Dic_Iterator_Next(&rd_iter)) {

		RenderData* rd = rd_iter.data;
		
		glUseProgram(rd_iter.key);

		dic_iter  = Dic_Iterator_Get(&(rd->renderer_lists));
		while (Dic_Iterator_Next(&dic_iter)) {
			InstanceList* il = dic_iter.data;
			vec_iter = Vec_Iterator_Get(&(il->instances));
			glBindVertexArray(il->mesh_id);

			while (Vec_Iterator_Next(&vec_iter)) {

			RenderComponent* rc = vec_iter.data;
			rc->mat.fnc(rc->mat.shader_id, rc->mat.data);

			SetModels(1, rc->transform);
			glDrawElementsInstanced(GL_TRIANGLES, il->index_count, GL_UNSIGNED_INT, 0,1);
			}
		}

		dic_iter = Dic_Iterator_Get(&(rd->multiple_renderer_lists));
		while (Dic_Iterator_Next(&dic_iter)) {
			MultipleInstanceList* mil = dic_iter.data;
			vec_iter = Vec_Iterator_Get(&(mil->instances));
			
			glBindVertexArray(mil->mesh_id);
			mil->material.fnc(mil->material.shader_id, mil->material.data);

			SetModels(mil->instances.count, mil->instances.buffer);
		
			glDrawElementsInstanced(GL_TRIANGLES, mil->index_count, GL_UNSIGNED_INT, 0, mil->instances.count);
		}
	}
	

	glBindVertexArray(0);
}

