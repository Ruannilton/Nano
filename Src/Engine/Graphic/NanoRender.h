#ifndef NANO_RENDER
#define NANO_RENDER

#include "../Core/NanoCore.h"
#include "Color.h"
#include "Camera.h"
#include "Material.h"
#include "Mesh.h"
#include "Shader.h"
#include "RenderComponent.h"
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

UNIQUE Scene* current_scene;
UNIQUE Camera* current_camera;

UNIQUE uint matrix_buffer = 0;
UNIQUE uint lights_buffer = 0;

inline PointLight* Render_AddPointLight(Scene* scn) {
	return  Scene_AddPointLight(current_scene);
}

inline SpotLight* Render_AddSpotLight(Scene* scn) {
	return Scene_AddSpotLight(current_scene);
}

inline DirectionalLight* Render_GetSun() {
	return &(current_scene->sun);
}

inline RenderComponent Renderer_AddComponent(uint shader, uint mesh) {
	return Scene_AddRenderComponent(current_scene, shader, mesh);
}

void Renderer_Init();

void Renderer_SetScene(Scene* scn);

void Renderer_RenderScene();

void Renderer_SetupProjection();

void Renderer_SetupLighting();

#endif // !NANO_RENDER


