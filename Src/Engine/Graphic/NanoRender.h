#ifndef NANO_RENDER
#define NANO_RENDER

#include "../Core/NanoCore.h"
#include "Color.h"
#include "Camera.h"
#include "Material.h"
#include "Mesh.h"
#include "Shader.h"
#include "RenderComponent.h"
#include "CubeMap.h"
#include "Lights/Light.h"
#include "../Architecture/Scene.h"

#define SHADER_POS_LOC 0
#define SHADER_COLOR_LOC 1
#define SHADER_TEX_LOC 2
#define SHADER_NORM_LOC 3
#define SHADER_MODEL_LOC 4
#define SHADER_VIEW_LOC 5
#define SHADER_PROJ_LOC 6

#define SHADER_UNIFORM_MATRIX_LOC 0
#define SHADER_UNIFORM_LIGHT_LOC 1
#define SHADER_UNIFORM_MODEL_LOC 2

UNIQUE Scene* current_scene;
UNIQUE Camera* current_camera;

UNIQUE uint matrix_buffer = 0;
UNIQUE uint lights_buffer = 0;
UNIQUE uint models_buffer = 0;
UNIQUE uint model_buffer  = 0;

inline PointLight* Renderer_AddPointLight(Scene* scn,Vec3 pos) {
	PointLight* pl = 0;
	pl = Scene_AddPointLight(current_scene);
if (pl) {
	pl->Ambient.x =  0.2f;
	pl->Ambient.y = 0.2f;
	pl->Ambient.z = 0.2f;

	pl->Diffuse.x = 0.8f;
	pl->Diffuse.y = 0.8f;
	pl->Diffuse.z = 0.8f;

	pl->Specular.x = 1.0f;
	pl->Specular.y = 1.0f;
	pl->Specular.z = 1.0f;

	pl->Position = pos;

	pl->Color.x = 1;
	pl->Color.y = 1;
	pl->Color.z = 1;

	pl->Constant = 1;
	pl->Linear = 0.07f;
	pl->Quadratic = 0.017;
	}
	return pl;
}

inline SpotLight* Renderer_AddSpotLight(Scene* scn) {
	return Scene_AddSpotLight(current_scene);
}

inline DirectionalLight* Renderer_GetSun() {
	return &(current_scene->sun);
}

inline RenderComponent* Renderer_AddComponent(Mesh* mesh,Material* mat,Vec3 position) {
	RenderComponent* r = Scene_AddRenderComponent(current_scene, mat, mesh->mesh_id, mesh->index_count);
	RenderComponent_SetPosition(r,position);
	return r;
}

inline SharedRenderComponent Renderer_AddSharedRenderComponent(Mesh* mesh, Material* mat, uint count) {
	 return Scene_AddSharedRenderComponent(current_scene, mat, mesh->mesh_id, mesh->index_count, count);
}

void Renderer_Init();

void Renderer_SetScene(Scene* scn);

void Renderer_RenderScene();

void Renderer_SetupProjection();

void Renderer_SetupLighting();

#endif // !NANO_RENDER


