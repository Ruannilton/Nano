#include "NanoRender.h"

#define MAT_SIZE (3 * sizeof(mat4))
#define LIGHT_SIZE (sizeof(vec4) + 5*(sizeof(vec4)) + 256*128)
#define MODEL_SIZE (1024*sizeof(mat4))

inline void Renderer_Shadow_Init() {
	glGenTextures(1, &render_env.depth_texture);
	glBindTexture(GL_TEXTURE_2D, render_env.depth_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, render_env.depth_texture_res.x, render_env.depth_texture_res.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float border[4] = { 1.0f,1.0f,1.0f,1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);

	glGenFramebuffers(1, &render_env.depth_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, render_env.depth_fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, render_env.depth_texture, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		DEBUG_C(ANSI_RED, "Framebuffer is not ready");
	}

	render_env.shadowShader = Shader_CreateShader("Assets/Shaders/defaultShadow.vert", "Assets/Shaders/defaultShadow.frag");
	glm_ortho(-10, 10, -10, 10, render_env.directional_light_shadow_cast_near, render_env.directional_light_shadow_cast_far, render_env.directional_light_proj);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer_Init() {

	glGenBuffers(1, &render_env.matrix_buffer);
	glBindBuffer(GL_UNIFORM_BUFFER, render_env.matrix_buffer);
	glBufferData(GL_UNIFORM_BUFFER, MAT_SIZE, 0, GL_DYNAMIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER, SHADER_UNIFORM_MATRIX_LOC, render_env.matrix_buffer, 0, MAT_SIZE);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glGenBuffers(1, &render_env.lights_buffer);
	glBindBuffer(GL_UNIFORM_BUFFER, render_env.lights_buffer);
	glBufferData(GL_UNIFORM_BUFFER, LIGHT_SIZE, NULL, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, SHADER_UNIFORM_LIGHT_LOC, render_env.lights_buffer);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glGenBuffers(1, &render_env.model_buffer); //init after

	Renderer_Shadow_Init();
	
}

void Renderer_SetupMatrices() {
	if (current_camera != NULL) {
		glBindBuffer(GL_UNIFORM_BUFFER, render_env.matrix_buffer);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(mat4), current_camera->projection);
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(mat4), sizeof(mat4), current_camera->view);
		glBufferSubData(GL_UNIFORM_BUFFER, 2*sizeof(mat4), sizeof(mat4), render_env.light_matrix);
		glBindBufferRange(GL_UNIFORM_BUFFER, SHADER_UNIFORM_MATRIX_LOC, render_env.matrix_buffer, 0, 3 * sizeof(mat4));
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}

void Renderer_SetupLighting() {
	
	glBindBuffer(GL_UNIFORM_BUFFER, render_env.lights_buffer);
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
	Renderer_SetupMatrices();
}

void SetModels(uint count, mat4* models) {
	glBindBuffer(GL_ARRAY_BUFFER, render_env.model_buffer);
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

void Renderer_RenderShadows() {
	
	glViewport(0, 0, render_env.depth_texture_res.x, render_env.depth_texture_res.y);
	glBindFramebuffer(GL_FRAMEBUFFER, render_env.depth_fbo);
	glUseProgram(render_env.shadowShader);
	glUniformMatrix4fv(10, 1, GL_FALSE, &render_env.light_matrix);
	glClear(GL_DEPTH_BUFFER_BIT);

	glm_lookat(current_scene->sun.Position.arr, current_scene->sun.Direction.arr, Y_Axis,render_env.directional_ligh_view);
	glm_mat4_mul(render_env.directional_light_proj, render_env.directional_ligh_view, render_env.light_matrix);

	Dic_Iterator rd_iter = Dic_Iterator_Get(&(current_scene->render_data));
	Dic_Iterator dic_iter;
	Vec_Iterator vec_iter;

	while (Dic_Iterator_Next(&rd_iter)) {

		RenderData* rd = rd_iter.data;
		dic_iter = Dic_Iterator_Get(&(rd->renderer_lists));
		while (Dic_Iterator_Next(&dic_iter)) {
			
			InstanceList* il = dic_iter.data;
			vec_iter = Vec_Iterator_Get(&(il->instances));
			glBindVertexArray(il->mesh_id);

			while (Vec_Iterator_Next(&vec_iter)) {
				RenderComponent* rc = vec_iter.data;
				SetModels(1, rc->transform);
				glDrawElementsInstanced(GL_TRIANGLES, il->index_count, GL_UNSIGNED_INT, 0, 1);
			}
		}

		dic_iter = Dic_Iterator_Get(&(rd->multiple_renderer_lists));
		while (Dic_Iterator_Next(&dic_iter)) {
			MultipleInstanceList* mil = dic_iter.data;
			vec_iter = Vec_Iterator_Get(&(mil->instances));

			glBindVertexArray(mil->mesh_id);
			SetModels(mil->instances.count, mil->instances.buffer);
			glDrawElementsInstanced(GL_TRIANGLES, mil->index_count, GL_UNSIGNED_INT, 0, mil->instances.count);
		}
	}

	glViewport(0, 0, nano->window_widht, nano->window_height);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void Renderer_RenderObjects() {
	Camera_UpdateView(current_camera);
	Renderer_SetupMatrices();
	Skybox_Use(&current_scene->sky);

	Dic_Iterator rd_iter = Dic_Iterator_Get(&(current_scene->render_data));
	Dic_Iterator dic_iter;
	Vec_Iterator vec_iter;

	while (Dic_Iterator_Next(&rd_iter)) {

		RenderData* rd = rd_iter.data;

		glUseProgram(rd_iter.key);
		Shader_SetInt(rd_iter.key, "ShadowMap", 16);
		Shader_SetTextureUnit(render_env.depth_texture, GL_TEXTURE16);
	


		dic_iter = Dic_Iterator_Get(&(rd->renderer_lists));
		while (Dic_Iterator_Next(&dic_iter)) {
			InstanceList* il = dic_iter.data;
			vec_iter = Vec_Iterator_Get(&(il->instances));
			glBindVertexArray(il->mesh_id);

			while (Vec_Iterator_Next(&vec_iter)) {

				RenderComponent* rc = vec_iter.data;
				rc->mat.fnc(rc->mat.shader_id, rc->mat.data);

				SetModels(1, rc->transform);
				glDrawElementsInstanced(GL_TRIANGLES, il->index_count, GL_UNSIGNED_INT, 0, 1);
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

}

void Renderer_RenderScene() {
	
	Renderer_SetupLighting();
	Renderer_RenderShadows();
	Renderer_RenderObjects();
}

