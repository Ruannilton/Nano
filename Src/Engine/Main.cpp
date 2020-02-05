extern "C" {
#include "NanoEngine.h"
#include "..//Materials/TexturedMaterial.h"
}


 void Start() {


	 mesh_loader_pre_alloc = mbyte(10);

	Texture* wood_box = texture_LoadTextureDefault("Assets/Images/wood_box.png");
	Texture* specular_wood_box = texture_LoadTextureDefault("Assets/Images/specular_wood_box.png");
	Texture* cerberus = texture_LoadTextureDefault("Assets/Images/Cerberus_A.png");

	Mesh* cube_mesh = mesh_LoadPrimitive(PRIMITIVE_CUBE);

	Material* color_mat = CNEW(TexturedMaterial, DefaultShader, wood_box, wood_box, specular_wood_box);
	RenderComponent* cerb = RenderComponent_Create(cube_mesh, color_mat);
	RC_SetPosition(cerb, vec3{ 1,0,0 });
	AddToRender(cerb);

	Material* color_mat2 = CNEW(TexturedMaterial, DefaultShader, cerberus, cerberus, cerberus);
	RenderComponent* cerb2 = RenderComponent_Create(cube_mesh, color_mat2);
	RC_SetPosition(cerb2, vec3{ -1,0,0 });
	AddToRender(cerb2);
}
 
 void Update() {

	
	 vec3 mouse_mov = { (float)mouse_delta_x, (float)mouse_delta_y, 0 };
	 camera_Rotate(&currentCamera, mouse_mov);
	 
	 if (mouse_delta_scroll_y != 0) {
		 camera_Zoom(&currentCamera, mouse_delta_scroll_y);
	 }
	 
	 vec3 left = { -5.5f*delta_time,0,0 };
	 vec3 right = {  5.5f * delta_time,0,0 };
	 vec3 foward = { 0,0,5.5f * delta_time };
	 vec3 backward = { 0.0f,0,-5.5f * delta_time };

	 if (Key(GLFW_KEY_A)) {
		 camera_Translate(&currentCamera, left);
	 }
	 if (Key(GLFW_KEY_D)) {
		 camera_Translate(&currentCamera, right);
	 }
	 if (Key(GLFW_KEY_W)) {
		 camera_Translate(&currentCamera, foward);
	 }
	 if (Key(GLFW_KEY_S)) {
		 camera_Translate(&currentCamera, backward);
	 }
	 
 }