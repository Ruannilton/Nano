#include "NanoEngine.h"

Mesh* plane;
Texture* texture;
RenderComponent* rc;

Material texMaterial;

typedef struct TexturedMaterial {
	GLuint tex_id;
};

void TexturedMaterialFnc(GLuint shader, void* data) {
	TexturedMaterial* dat = (TexturedMaterial*)data;
	glBindTexture(shader, dat->tex_id);
}

TexturedMaterial matData;

 void Start() {

	 texMaterial.shader_id = DefaultShader;
	 texMaterial.fnc = TexturedMaterialFnc;

	 mesh_loader_pre_alloc = kbyte(50);
	 plane = mesh_LoadMesh("Assets/models/Cerberus.obj");
	 texture = texture_LoadTextureDefault("Assets/Images/Rat.png");
	 matData.tex_id = texture->id;
	 rc = RenderComponent_Create(plane,&texMaterial, &matData);

	 AddRenderComponent(rc);
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