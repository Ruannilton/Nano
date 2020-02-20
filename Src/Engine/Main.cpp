extern "C" {
#include "NanoEngine.h"
#include "..//Materials/TexturedMaterial.h"
}

void Setup() {
	Input_SetMouse(GLFW_MOUSE_BUTTON_LAST + 1, 0.025);
	nano->multisamples_level = 8;
	Nano_SetWindowSize(800, 600);
}

void Loader() {

}

 void Start() {

	 Scene* myScene = Scene_Create(2);
	 Scene_SetBackground(myScene, { 0.8,0.8,1,1 });
	 Camera_SetPosition(myScene->camera_scene, { 0,0,-10 });
     Renderer_SetScene(myScene);

	 PointLight* pl = Renderer_AddPointLight(myScene, {0,4,-5});
	 pl->Color = { 0.02f,0,1 };

	 PointLight* pl2 = Renderer_AddPointLight(myScene, { 0,4, 5 });
	 pl2->Color = { 1,0,0.02f };

	 Mesh* ksr29 = Mesh_LoadMesh("Assets/ksr29/ksr29.obj");
	 Texture* texture_color = Texture_LoadTextureDefault("Assets/ksr29/color.jpg");
	 Texture* texture_specular = Texture_LoadTextureDefault("Assets/ksr29/spec.jpg");
	 Shader Default = Scene_LoadShader(myScene,"Assets/Shaders/default.vert", "Assets/Shaders/default.frag");
	 Material* mat = CNEW(TexturedMaterial, Default, texture_color, texture_specular);

	 int i = -3;
	 for (; i < 3; i++) {
		 RenderComponent rc = Renderer_AddComponent(ksr29, mat, { 0,0, i*2.0f });
	 }
	 


	//Scene_ShowRenderInfo(current_scene);
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
	 if (Input_KeyRelease(GLFW_KEY_F)) {
		 Nano_TogleFullScreen();
	 }
	 
 }

 void Cleanup() {

 }