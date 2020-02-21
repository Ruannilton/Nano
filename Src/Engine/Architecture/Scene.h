#ifndef NANO_SCENE
#define NANO_SCENE

#define MAX_LIGHTS 256

#include "../Utils.h"
#include "../Graphic/Camera.h"
#include "../DataStructures/dynamic_vector.h"
#include "../DataStructures/hash_map.h"
#include "../Graphic/Lights/Light.h"
#include "../Graphic/Color.h"
#include "RenderData.h"

typedef struct {
	Camera* camera_scene;
	Color BackGroundColor;
	DirectionalLight sun;

	Vector point_lights;
	Vector spot_lights;
	uint light_count;
	Dictionary(Shader,RenderData) render_data;
}Scene;

UNIQUE uint Default_Scene_PointLight_Prealoc_count = 16;
UNIQUE uint Default_Scene_SpotLight_Prealoc_count = 16;

inline PointLight* Scene_AddPointLight(Scene* scn) {
	if (scn->light_count < MAX_LIGHTS) {
		return Vector_Push(PointLight, &scn->point_lights, 0);
		scn->light_count++;
	}
}

inline SpotLight* Scene_AddSpotLight(Scene* scn) {
	if (scn->light_count < MAX_LIGHTS) {
		return Vector_Push(SpotLight, &scn->spot_lights, 0);
		scn->light_count++;
	}
}

Shader Scene_LoadShader(Scene* scn, string vert, string frag);
Scene* Scene_Create(uint shader_count);

void Scene_SetBackground(Scene* scn,Color color);
void Scene_SetCamera(Scene* scn, Camera* cam);
void Scene_AddShader(Scene* scn, Shader shader,uint mesh_count);
void Scene_ShowRenderInfo(Scene* scn);

RenderComponent* Scene_AddRenderComponent(Scene* scene, Material* mat, uint mesh_id,uint index_c);
SharedRenderComponent Scene_AddSharedRenderComponent(Scene* scene, Material* mat, uint mesh_id, uint index_c, uint count);

#endif