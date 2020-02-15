#ifndef NANO_SCENE
#define NANO_SCENE

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
	Vector static_scene_point_lights;
	Vector static_scene_spot_lighs;

	Dictionary(Shader,RenderData) render_data;
}Scene;

Scene* Scene_Create(uint shader_count);

void Scene_SetBackground(Scene* scn,Color color);
void Scene_SetCamera(Scene* scn, Camera* cam);
void Scene_AddShader(Scene* scn, Shader shader,uint mesh_count);
void Scene_ShowRenderInfo(Scene* scn);

RenderComponent Scene_AddRenderComponent(Scene* scene, uint shader, uint mesh_id);

#endif