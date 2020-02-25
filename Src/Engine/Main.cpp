extern "C" {
#include "NanoEngine.h"
#include "..//Materials/TexturedMaterial.h"
}

void Setup() {
	Input_SetMouse(GLFW_MOUSE_BUTTON_LAST + 1, 0.025);
	nano->multisamples_level = 16;
	Nano_SetWindowSize(800, 600);
}

void Loader() {

}

void Start() {
	Skybox_Init();
	Scene* myScene = Scene_Create(2);
	Scene_SetBackground(myScene, { 0.8,0.8,1,1 });
	Camera_SetPosition(myScene->camera_scene, { 0,0,-10 });
	Renderer_SetScene(myScene);

	PointLight* pl = Renderer_AddPointLight(myScene, { 3,2,-3 });
	pl->Color = { 0.02f,0,1 };

	PointLight* pl2 = Renderer_AddPointLight(myScene, { 2,4, 5 });
	pl2->Color = { 1,0,0.02f };

	Mesh* ksr29 = Mesh_LoadMesh("Assets/ksr29/ksr29.obj");
	Mesh* cerberus = Mesh_LoadMesh("Assets/models/Cerberus.obj");

	Texture* ksr_color = Texture_LoadTextureDefault("Assets/ksr29/color.jpg");
	Texture* ksr_specular = Texture_LoadTextureDefault("Assets/ksr29/spec.jpg");
	Texture* cerbers_color = Texture_LoadTextureDefault("Assets/Images/Cerberus_A.png");


	const char* sky_path[6] = {"Assets/Images/skybox/right.jpg",
							   "Assets/Images/skybox/left.jpg",
							   "Assets/Images/skybox/top.jpg",
							   "Assets/Images/skybox/bottom.jpg",
							   "Assets/Images/skybox/back.jpg",
							   "Assets/Images/skybox/front.jpg"};

	 CubeMap* sky = CubeMap_LoadTextureDefault(sky_path);

	 Shader Default = Scene_LoadShader(myScene,"Assets/Shaders/default.vert", "Assets/Shaders/default.frag");
	 Shader SkyboxShader = Shader_CreateShader("Assets/Shaders/skybox.vert", "Assets/Shaders/skybox.frag");
	 Skybox* skb = Skybox_Create(SkyboxShader, *sky);
	 Scene_SetSkybox(myScene, *skb);

	 Material* ksr_mat = CNEW(TexturedMaterial, Default, ksr_color, ksr_specular);
	 Material* cerberus_mat = CNEW(TexturedMaterial, Default, cerbers_color, cerbers_color);

	
	 
	 int s = 4;

	SharedRenderComponent ksrs = Renderer_AddSharedRenderComponent(ksr29, ksr_mat, s);

	 Vec_Iterator vec_iter = Vec_Iterator_Get(ksrs.transforms);
	 int i = 0;
	 while (Vec_Iterator_Next(&vec_iter)) {
		 mat4* p = (mat4*)vec_iter.data;
		 vec3 v = { 0,0, i * 2.0f };
		 glm_translate(*p, v);
		 i++;
	 } 

	//Scene_ShowRenderInfo(current_scene);
}
 
 void Update() {

	
	 Camera_SeekMouse(current_camera);
	 float vel = 15.0f;
	 Vec3 left = { -vel *delta_time,0,0 };
	 Vec3 right = { vel * delta_time,0,0 };
	 Vec3 foward = { 0,0,vel * delta_time };
	 Vec3 backward = { 0.0f,0,-vel * delta_time };

	
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