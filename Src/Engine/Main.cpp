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
	Scene* myScene = Scene_Create(16);

	Scene_SetBackground(myScene, { 0.8f,0.8f,1,1 });
	Camera_SetPosition(myScene->camera_scene, { 0,1,-5 });
	Renderer_SetScene(myScene);

	DirectionalLight* sun = Renderer_GetSun();
	sun->Position = { 0,15,0 };
	sun->Direction = { 8,-0.5,8 };
	sun->Ambient = { 0.1f,0.1f,0.1f };
	sun->Diffuse = {0.8,0.8,0.8};
	sun->Color = { 1,1,1 };
	

	PointLight* pl = Renderer_AddPointLight(myScene, { 0,1,-10 });
	PointLight* pl2 = Renderer_AddPointLight(myScene, { 0,1, 10 });
	
	pl->Color = { 0.02f,0,1 };
	pl2->Color = { 1,0,0.02f };

	Shader Default = Scene_LoadShader(myScene, "Assets/Shaders/default.vert", "Assets/Shaders/default.frag");
	Shader SkyboxShader = Shader_CreateShader("Assets/Shaders/skybox.vert", "Assets/Shaders/skybox.frag");

	Mesh* ksr29 = Mesh_LoadMesh("Assets/ksr29/ksr29.obj");
	Mesh* plane = Mesh_LoadPrimitive(PRIMITIVE_PLANE);
	
	Texture* ksr_color = Texture_LoadTextureDefault("Assets/ksr29/color.jpg");
	Texture* ksr_specular = Texture_LoadTextureDefault("Assets/ksr29/spec.jpg");
	Texture* white = Texture_LoadTextureDefault("Assets/images/white.png");
	Texture* black = Texture_LoadTextureDefault("Assets/images/black.png");
	const char* sky_path[6] = CubeMap_GetPath(Assets/Images/skybox/,jpg);
	CubeMap* sky_texture = CubeMap_LoadTextureDefault(sky_path);

	
	Skybox* sky = Skybox_Create(SkyboxShader, *sky_texture);
	Scene_SetSkybox(myScene, *sky);

	Material* ksr_mat = CNEW(TexturedMaterial, Default, ksr_color, ksr_specular);
	Material* floor_mat = CNEW(TexturedMaterial, Default, white, white);

	RenderComponent* floor = Renderer_AddComponent(plane, floor_mat, { 0,-1,20 });
	RenderComponent_Rotate(floor, { 90,180,0 });
	RenderComponent_Scale(floor, { 1000000,100000,0 });

	SharedRenderComponent ksrs = Renderer_AddSharedRenderComponent(ksr29, ksr_mat, 4);
	Vec_Iterator vec_iter = Vec_Iterator_Get(ksrs.transforms);

	 while (Vec_Iterator_Next(&vec_iter)) {
		 mat4* p = (mat4*)vec_iter.data;
		 vec3 v = { 0,2, vec_iter.current * 2.0f };
		 glm_translate(*p, v);
	 } 

	Scene_ShowRenderInfo(current_scene);
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