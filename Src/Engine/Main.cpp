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
	 Scene_SetBackground(myScene, { 0,0,0,1 });
	 Camera_SetPosition(myScene->camera_scene, { 0,0,-10 });
     Renderer_SetScene(myScene);

	 DirectionalLight* dl= Renderer_GetSun();
	 dl->Ambient = Light_Val(0.2f); 
	 dl->Diffuse = Light_Val(0.6f);
	 dl->Specular = Light_Val(1);
	 dl->Direction = { 0.2f ,-0.5f, 1 };
	 dl->Color = { 1,1,1 };

	 PointLight* pl = Renderer_AddPointLight(myScene);
	 pl->Ambient = Light_Val(0.8f);
	 pl->Diffuse = Light_Val(0.8f);
	 pl->Specular = Light_Val(1);
	 pl->Position = { 1,1,-10 };
	 pl->Color = { 0,0,1 };
	 pl->Constant = 1;
	 pl->Linear = 0.07f;
	 pl->Quadratic = 0.017;

	 PointLight* pl2 = Renderer_AddPointLight(myScene);
	 pl2->Ambient = Light_Val(0.2f);
	 pl2->Diffuse = Light_Val(0.8f);
	 pl2->Specular = Light_Val(1);
	 pl2->Position = { 1,1,1 };
	 pl2->Color = { 1,0,0 };
	 pl2->Constant = 1;
	 pl2->Linear = 0.07f;
	 pl2->Quadratic = 0.017;
	 
	Texture* cerberus_tex = Texture_LoadTextureDefault("Assets/Images/Cerberus_A.png");
	Mesh* cerberus_mesh = Mesh_LoadMesh("Assets/models/Cerberus.obj");
	Shader DefaultShader = Shader_CreateShader("Assets/Shaders/default.vert", "Assets/Shaders/default.frag");

	Material* color_mat = CNEW(TexturedMaterial, DefaultShader, cerberus_tex, cerberus_tex, cerberus_tex);

	Scene_AddShader(myScene, DefaultShader, 3);
	
	RenderComponent rc = Renderer_AddComponent(DefaultShader, cerberus_mesh->mesh_id,cerberus_mesh->index_count);
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