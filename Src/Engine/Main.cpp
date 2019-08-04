#include "NanoEngine.h"

Mesh* plane;
Texture* texture;
RenderComponent rc;


 void Start() {

	 mesh_loader_pre_alloc = kbyte(50);
	 plane = mesh_LoadMesh("Assets/models/Cerberus.obj");
	 texture = texture_LoadTextureDefault("Assets/Images/Rat.png");
	 _RenderComponent(&rc,DefaultShader.ID,texture->id, mesh_genVAO(plane),plane->indexCount);
	 AddRenderComponent(&rc);
}
 
 void Update() {
	
	 if (KeyHold(GLFW_KEY_A)) {
		 currentCamera.position[0] -= 0.1f;
	 }
	 if (KeyHold(GLFW_KEY_D)) {
		 currentCamera.position[0] += 0.1f;
	 }
	 if (KeyHold(GLFW_KEY_W)) {
		 currentCamera.position[2] -= 0.1f;
	 }
	 if (KeyHold(GLFW_KEY_S)) {
		 currentCamera.position[2] += 0.1f;
	 }
	 currentCamera.rotation[0] += mouse_offsetY;
	 currentCamera.rotation[1] += mouse_offsetX;
	
 }