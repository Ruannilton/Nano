extern "C" {
#include "NanoEngine.h"
#include "..//Materials/TexturedMaterial.h"
#include "..//Materials/ColorMaterial.h"
}


 void Start() {

	 //Heap corruption bug 
	 //Press continue until run

	mesh_loader_pre_alloc = mbyte(10); // alloca 10 mb para o carregamento dos modelos, será feito automaticamente futuramente

	//Shader colorShader = shader_CreateShader("Assets/Shaders/color.vert", "Assets/Shaders/color.frag");
	Material* color_mat = CNEW(TexturedMaterial, DefaultShader, "Assets/Images/wood_box.png", "Assets/Images/wood_box.png", "Assets/Images/specular_wood_box.png");
	Mesh* cube_mesh = mesh_LoadPrimitive(PRIMITIVE_CUBE);
	RenderComponent* cerb = RenderComponent_Create(cube_mesh, color_mat);
	RC_SetPosition(cerb, vec3{ 0,0,0 });
	AddToRender(cerb);

	 
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