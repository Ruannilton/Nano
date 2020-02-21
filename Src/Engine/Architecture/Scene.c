#include "Scene.h"
#include "../../Materials/TexturedMaterial.h"


void Scene_SetBackground(Scene* scn, Color color) {
	scn->BackGroundColor = color;
}

void Scene_SetCamera(Scene* scn, Camera* cam) {
	scn->camera_scene = cam;
}

Scene* Scene_Create(uint shader_count) {
	Scene* scn = NEW(Scene);
	VERIFY(scn, NULL);
	
	scn->camera_scene = NEW(Camera);
	scn->render_data = Dictionary_Create(RenderData, shader_count, hash_f);
	scn->point_lights = Vector_Create(PointLight, Default_Scene_PointLight_Prealoc_count);
	scn->spot_lights = Vector_Create(SpotLight, Default_Scene_SpotLight_Prealoc_count);
	scn->light_count = 0;

	scn->sun.Ambient.x =  0.2f;
	scn->sun.Ambient.y = 0.2f;
	scn->sun.Ambient.z = 0.2f;
	
	scn->sun.Diffuse.x = 0.6f;
	scn->sun.Diffuse.y = 0.6f;
	scn->sun.Diffuse.z = 0.6f;

	scn->sun.Specular.x = 1;
	scn->sun.Specular.y = 1;
	scn->sun.Specular.z = 1;

	scn->sun.Color.x = 1;
	scn->sun.Color.y = 1;
	scn->sun.Color.z = 1;

	scn->sun.Direction.x = 0;
	scn->sun.Direction.y = -0.5f;
	scn->sun.Direction.z = 1;

	Camera_CreateCamera(scn->camera_scene, (Vec3){ 0,0,0 });
	Color_SetColor(0, 1, 1, 1, scn->BackGroundColor);
	return scn;
}

void Scene_AddShader(Scene* scn, Shader shader,uint mesh_count) {

	RenderData* rd = Dictionary_Add(RenderData, &(scn->render_data), (void*)shader);


	rd->renderer_lists = Dictionary_Create(InstanceList, mesh_count, hash_f);
	rd->multiple_renderer_lists = Dictionary_Create(MultipleInstanceList, mesh_count, hash_f);
}

Shader Scene_LoadShader(Scene* scn, string vert, string frag) {
	Shader s = Shader_CreateShader("Assets/Shaders/default.vert", "Assets/Shaders/default.frag");
	Scene_AddShader(scn, s, 4);
	return s;
}


RenderComponent* Scene_AddRenderComponent(Scene* scene, Material* mat, uint mesh_id,uint index_c) {
	
	RenderData* rd = Dictionary_Get(RenderData, &(scene->render_data), (void*)mat->shader_id);
	RenderComponent* rc = NULL;
	

	if (rd) {
		InstanceList* il = Dictionary_Get(InstanceList, &rd->renderer_lists, mesh_id);
		
		if (!il) {
			il= Dictionary_Add(InstanceList, &rd->renderer_lists, mesh_id);
			InstanceList_Create(il, mesh_id, 1);
		}

		rc = Vector_Push(RenderComponent, &il->instances, NULL);
		il->index_count = index_c;
		memcpy(rc->transform, identity, sizeof(identity));
		memcpy(&(rc->mat), mat, sizeof(Material));

	}

	return rc;
}

SharedRenderComponent Scene_AddSharedRenderComponent(Scene* scene, Material* mat, uint mesh_id, uint index_c, uint count) {
	
	RenderData* rd = Dictionary_Get(RenderData, &(scene->render_data), (void*)mat->shader_id);
	SharedRenderComponent rc;

	if (rd) {
		MultipleInstanceList* mil = Dictionary_Get(MultipleInstanceList, &rd->multiple_renderer_lists, mesh_id);
		
		if (!mil) {
			mil = Dictionary_Add(MultipleInstanceList, &rd->multiple_renderer_lists, mesh_id);
		}
		memcpy(&mil->material, mat, sizeof(Material));
		mil->mesh_id = mesh_id;
		mil->index_count = index_c;
		mil->instances = Vector_Create(mat4, count);
		
		uint i = 0;
		for (; i < count;i++) {
			mat4* m = Vector_Push(mat4, &mil->instances, NULL);
			memcpy(m, identity, sizeof(mat4));
		}
		
		rc.mat = &mil->material;
		rc.transforms = &mil->instances;
		
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
						Vec_Iterator it = Vec_Iterator_Get(&il->instances);
						
						while (Vec_Iterator_Next(&it))
						{
							if (it.data) {

							RenderComponent* instance = it.data;
							TexturedMaterial* cm = instance->mat.data;
							DEBUG_C(ANSI_LIGHT_BLUE, "\t\t\tTexture: %d", cm->difffuse->id);
							}
						}
					}
				}
			}
			DEBUG_C(ANSI_LIGHT_BLUE, "\t\tInstancePoolList[%d/%d]:",0,0);
			
		}
	}
	
}