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


	 Scene* myScene = Scene_Create(2,2,2);
	 Scene_SetBackground(myScene, { 0,1,1,1 });
	 Camera_SetPosition(myScene->camera_scene, { 0,0,-10 });
     Renderer_SetScene(myScene);

	Texture* wood_box = Texture_LoadTextureDefault("Assets/Images/wood_box.png");
	Texture* specular_wood_box = Texture_LoadTextureDefault("Assets/Images/specular_wood_box.png");
	
	Mesh* cube_mesh = Mesh_LoadPrimitive(PRIMITIVE_CUBE);
	Shader DefaultShader = Shader_CreateShader("Assets/Shaders/simple.vert", "Assets/Shaders/simple.frag");
	Material* color_mat = CNEW(TexturedMaterial, DefaultShader, wood_box, wood_box, specular_wood_box);

	Scene_AddShader(myScene, DefaultShader, 3);
	
	RenderComponent rc = Renderer_AddComponent(DefaultShader, cube_mesh->mesh_id);
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

	 DEBUG_C(ANSI_MAGENTA, "Camera Pos: %f %f %f \n Camera Look: %f %f %f", current_camera->position.x, current_camera->position.y, current_camera->position.z, current_camera->rotation.x, current_camera->rotation.y, current_camera->rotation.z);

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