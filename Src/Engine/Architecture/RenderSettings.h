#ifndef NANO_RENDER_SETTINGS
#define NANO_RENDER_SETTINGS

#include "../Utils.h"

#define DEFAULT_RENDER_ENV {0,0,0,0,0,0,0,2048,2048,0.1f,20.0f}

typedef struct {
	uint matrix_buffer;
	uint lights_buffer;
	uint models_buffer;
	uint model_buffer;

	//shadows
	uint depth_fbo;
	uint depth_texture;
	Shader shadowShader;
	uiVec2 depth_texture_res;
	float directional_light_shadow_cast_near;
	float directional_light_shadow_cast_far;

	mat4 directional_light_proj;
	mat4 directional_ligh_view;
	mat4 light_matrix;
}RenderEnv;

#endif