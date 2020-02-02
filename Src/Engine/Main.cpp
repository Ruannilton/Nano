extern "C" {
#include "NanoEngine.h"
#include "..//Materials/TexturedMaterial.h"
}


 void Start() {

	mesh_loader_pre_alloc = mbyte(10);

	Material* dva_mat = CNEW(TexturedMaterial,DefaultShader, "Assets/Images/A_dva.png");
	Mesh* dva_mesh = mesh_LoadMesh("Assets/models/dva.obj");

	Material* cerb_mat = CNEW(TexturedMaterial, DefaultShader, "Assets/Images/Cerberus_A.png");
	Mesh* cerb_mesh = mesh_LoadMesh("Assets/models/Cerberus.obj");

	
	RenderComponent* dva = RenderComponent_Create(dva_mesh, dva_mat);
	RC_SetPosition(dva,  vec3{ 0.5f,-1,-2.5f });
	glm_scale(dva->transform, vec3{ 0.025f,0.025f,0.025f });
	AddToRender(dva);
	
	RenderComponent* cerb = RenderComponent_Create(cerb_mesh, cerb_mat);
	RC_SetPosition(cerb, vec3{ 0.5f,0,-1.5f });
	glm_scale(cerb->transform, vec3{ 0.75f,0.75f,0.75f });
	AddToRender(cerb);

	 setColor(1.0f,0.6f,1.0f,1.0f, AmbientLight);
	 AmbientIntensity = 0.75f;
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