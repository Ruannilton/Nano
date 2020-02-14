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
	dynamic_vector static_scene_point_lights;
	dynamic_vector static_scene_spot_lighs;

	HashMap(Shader,RenderData) render_data;
}Scene;

Scene* Scene_Create(int shader_count);

void Scene_Set_Background(Scene* scn,Color color);
void Scene_Set_Camera(Scene* scn, Camera* cam);
void Scene_Add_Shader(Scene* scn, Shader shader,uint mesh_count);
void Scene_Show_Render_Infor(Scene* scn);

RenderComponent Scene_Add_Render_Component(Scene* scene, uint shader, uint mesh_id);

#endif