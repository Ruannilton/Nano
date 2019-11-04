extern "C" {
#include "NanoEngine.h"
#include "..//Materials/TexturedMaterial.h"
}


 void Start() {

	TexturedMaterial* t_mat = NEW(TexturedMaterial);
	t_mat->texture = texture_LoadTextureDefault("Assets/Images/Rat.png");

	Material* mat = Material_Create(DefaultShader, Material_GetBindFnc(TexturedMaterial), t_mat);
	
	Mesh* m = mesh_LoadPrimitive(PRIMITIVE_PLANE);
	RenderComponent* rc = RenderComponent_Create(m, mat);
	vec3 pos = { -0.5f,0,0 };
	glm_translate(rc->transform, pos);
	AddToRender(rc);

	
}
 
 void Update() {

	 DEBUG("Mouse position:  %f , %f",mouse_Xpos,mouse_Ypos);

	 vec3 left = { -0.5f,0,0 };
	 vec3 right = {  0.5f,0,0 };
	 vec3 foward = { 0,0,0.5f };
	 vec3 backward = { 0.0f,0,-0.5f };

	 if (KeyPress(GLFW_KEY_A)) {
		 camera_Translate(&currentCamera, left);
	 }
	 if (KeyPress(GLFW_KEY_D)) {
		 camera_Translate(&currentCamera, right);
	 }
	 if (KeyPress(GLFW_KEY_W)) {
		 camera_Translate(&currentCamera, foward);
	 }
	 if (KeyPress(GLFW_KEY_S)) {
		 camera_Translate(&currentCamera, backward);
	 }
	 
 }