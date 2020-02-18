extern "C" {
#include "NanoEngine.h"
#include "..//Materials/TexturedMaterial.h"
}

void Setup() {
	Input_SetMouse(GLFW_MOUSE_BUTTON_LAST + 1, 0.025);
}

void Loader() {

}

 void Start() {

	 mesh_loader_pre_alloc = KBYTE(128);
	 Scene* myScene = Scene_Create(2,128,128);
	 Scene_SetBackground(myScene, { 0,1,1,1 });
	 Camera_SetPosition(myScene->camera_scene, { 0,0,-10 });
     Renderer_SetScene(myScene);

	 DirectionalLight* dl= Renderer_GetSun();
	 dl->Ambient = { 0.2f,0.2f,0.2f };
	 dl->Diffuse = { 0.6f,0.6f,0.6f };
	 dl->Specular = { 1,1,1 };
	 dl->Direction = { 0.2f ,-0.5f, 1 };


	Texture* wood_box = Texture_LoadTextureDefault("Assets/Images/Cerberus_A.png");
	Texture* specular_wood_box = Texture_LoadTextureDefault("Assets/Images/specular_wood_box.png");
	
	Mesh* cube_mesh = Mesh_LoadMesh("Assets/models/Cerberus.obj");
	Shader DefaultShader = Shader_CreateShader("Assets/Shaders/default.vert", "Assets/Shaders/default.frag");

	Material* color_mat = CNEW(TexturedMaterial, DefaultShader, wood_box, wood_box, specular_wood_box);

	Scene_AddShader(myScene, DefaultShader, 3);
	
	RenderComponent rc = Renderer_AddComponent(DefaultShader, cube_mesh->mesh_id,cube_mesh->index_count);
	RenderComponent_SetPosition(rc, { 0,0,0 });
	*rc.mat = *color_mat;



	Scene_ShowRenderInfo(current_scene);
}
 
 void Update() {

	
	 Camera_SeekMouse(current_camera);
	 
	 Vec3 left = { -5.5f*delta_time,0,0 };
	 Vec3 right = {  5.5f * delta_time,0,0 };
	 Vec3 foward = { 0,0,5.5f * delta_time };
	 Vec3 backward = { 0.0f,0,-5.5f * delta_time };

	
	 if (Input_Key(GLFW_KEY_A)) {
		 Camera_Translate(current_camera, left);
	 }
	 if (Input_Key(GLFW_KEY_D)) {
		 Camera_Translate(current_camera, right);
	 }
	 if (Input_Key(GLFW_KEY_W)) {
		 Camera_Translate(current_camera, foward);
	 }
	 if (Input_Key(GLFW_KEY_S)) {
		 Camera_Translate(current_camera, backward);
	 }
	 
 }

 void Cleanup() {

 }