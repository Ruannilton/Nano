#include "Scene.h"
#include "../../Materials/TexturedMaterial.h"


void Scene_SetBackground(Scene* scn, Color color) {
	scn->BackGroundColor = color;
}

void Scene_SetCamera(Scene* scn, Camera* cam) {
	scn->camera_scene = cam;
}

Scene* Scene_Create(uint shader_count, uint pointLight_count, uint spotLight_count) {
	Scene* scn = NEW(Scene);
	VERIFY(scn, NULL);
	
	scn->camera_scene = NEW(Camera);
	scn->render_data = Dictionary_Create(RenderData, shader_count, hash_f);
	scn->point_lights = Vector_Create(PointLight, pointLight_count);
	scn->spot_lights = Vector_Create(SpotLight, spotLight_count);
	
	Camera_CreateCamera(scn->camera_scene, (Vec3){ 0,0,0 });
	Color_SetColor(0, 1, 1, 1, scn->BackGroundColor);
	return scn;
}

void Scene_AddShader(Scene* scn, Shader shader,uint mesh_count) {
	RenderData* rd = Dictionary_Add(RenderData, &(scn->render_data), (void*)shader);
	rd->renderer_lists = Dictionary_Create(InstanceList, mesh_count, hash_f);

}



RenderComponent Scene_AddRenderComponent(Scene* scene, uint shader, uint mesh_id,uint index_c) {
	static mat4 identity = GLM_MAT4_IDENTITY_INIT;
	RenderData* rd = Dictionary_Get(RenderData, &(scene->render_data), (void*)shader);
	RenderComponent rc;
	rc.mesh_id = 0;

	if (rd) {
		InstanceList* il = Dictionary_Get(InstanceList, &rd->renderer_lists, mesh_id);
		if (!il) {
		 il= Dictionary_Add(InstanceList, &rd->renderer_lists, mesh_id);
		 InstanceList_Create(il, mesh_id, 1);
		}
	 Instance* instance = Vector_Push(Instance, &il->instances, NULL);
	 instance->index_count = index_c;
	 memcpy(instance->transform, identity, sizeof(identity));
	 rc.mesh_id = mesh_id;
	 rc.mat = &instance->material;
	 rc.transform = &instance->transform;
	}

	return rc;
}

void Scene_ShowRenderInfo(Scene* scn) {
	
	uint i = 0;
	DEBUG_C(ANSI_LIGHT_BLUE, "RenderInfo:");
	for (i = 0; i < scn->render_data.size; i++) {
		RenderData* render_data = Dictionary_Get(RenderData, &scn->render_data, (void*)i);
		if (render_data) {
			DEBUG_C(ANSI_LIGHT_BLUE, "\tRenderData[%d]:",i);
			if (render_data->renderer_lists.size!=0) {
				uint r = 0;
				DEBUG_C(ANSI_LIGHT_BLUE, "\t\tInstanceList[%d/%d]:", render_data->renderer_lists.count, render_data->renderer_lists.size);
				for (r = 0; r < render_data->renderer_lists.size; r++) {

					InstanceList* il = Dictionary_Get(InstanceList, &render_data->renderer_lists, (void*)r);
					if (il) {
						DEBUG_C(ANSI_LIGHT_BLUE, "\t\t\tInstances[id: %d]:", il->mesh_id);
						Iterator it = Iterator_Get(&il->instances);
						
						while (Iterator_Next(&it))
						{
							if (it.data) {

							Instance* instance = it.data;
							TexturedMaterial* cm = instance->material.data;
							DEBUG_C(ANSI_LIGHT_BLUE, "\t\t\tTexture: %d", cm->texture->id);
							}
						}
					}
				}
			}
			DEBUG_C(ANSI_LIGHT_BLUE, "\t\tInstancePoolList[%d/%d]:",0,0);
			
		}
	}
	
}