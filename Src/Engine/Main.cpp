extern "C" {
#include "NanoEngine.h"
#include "..//Materials/TexturedMaterial.h"

}


 void Start() {


	 Scene* myScene = Scene_Create(2);

	 Scene_Set_Background(myScene, { 0,1,1,1 });
	 Renderer_SetScene(myScene);

	Texture* wood_box = texture_LoadTextureDefault("Assets/Images/wood_box.png");
	Texture* specular_wood_box = texture_LoadTextureDefault("Assets/Images/specular_wood_box.png");
	Texture* cerberus = texture_LoadTextureDefault("Assets/Images/Cerberus_A.png");

	Texture* wood_box2 = texture_LoadTextureDefault("Assets/Images/example2.jpg");
	Texture* specular_wood_box2 = texture_LoadTextureDefault("Assets/Images/example2.jpg");
	Texture* cerberus2 = texture_LoadTextureDefault("Assets/Images/example2.jpg");

	Mesh* cube_mesh = mesh_LoadPrimitive(PRIMITIVE_CUBE);
	Mesh* plane_mesh = mesh_LoadPrimitive(PRIMITIVE_PLANE);

	Shader DefaultShader = shader_CreateShader("Assets/Shaders/default.vert", "Assets/Shaders/default.frag");

	Material* color_mat = CNEW(TexturedMaterial, DefaultShader, wood_box, wood_box, specular_wood_box);
	Material* color_mat2 = CNEW(TexturedMaterial, DefaultShader, wood_box2, wood_box2, specular_wood_box2);

	Scene_Add_Shader(myScene, DefaultShader, 3);
	
	RenderComponent rc = Renderer_AddComponent(DefaultShader, cube_mesh->mesh_id);
	*rc.mat = *color_mat;

	RenderComponent rc2 = Renderer_AddComponent(DefaultShader, cube_mesh->mesh_id);
	*rc2.mat = *color_mat2;

	RenderComponent rc3 = Renderer_AddComponent(DefaultShader, plane_mesh->mesh_id);
	*rc3.mat = *color_mat2;


	Scene_Show_Render_Infor(current_scene);
}
 
 void Update() {

	
	 camera_SeekMouse(current_camera);
	 
	 Vec3 left = { -5.5f*delta_time,0,0 };
	 Vec3 right = {  5.5f * delta_time,0,0 };
	 Vec3 foward = { 0,0,5.5f * delta_time };
	 Vec3 backward = { 0.0f,0,-5.5f * delta_time };

	 if (Key(GLFW_KEY_A)) {
		 camera_Translate(current_camera, left);
	 }
	 if (Key(GLFW_KEY_D)) {
		 camera_Translate(current_camera, right);
	 }
	 if (Key(GLFW_KEY_W)) {
		 camera_Translate(current_camera, foward);
	 }
	 if (Key(GLFW_KEY_S)) {
		 camera_Translate(current_camera, backward);
	 }
	 
 }