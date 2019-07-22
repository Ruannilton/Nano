#include "NanoEngine.h"


float vertices[] = {
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f 
};
unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
};

Mesh* plane;
Texture* texture;

RenderComponent rc;


 void Start() {
	
	 plane= mesh_BuildMesh(indices, vertices, POSITION_FLAG | COLOR_FLAG | UV_FLAG, SIZEVEC(indices),SIZEVEC(vertices));
	 
	 GLuint vao= mesh_genVAO(plane);
	 texture = texture_LoadTextureDefault("Assets/Images/Rat.png");

	 rc.Vao = vao;
	 rc.Shader = DefaultShader;
	 rc.Texture = texture->id;
	 rc.IndexCount = plane->indexCount;
	 memcpy(&rc.Model, MAT4_IDENTITY, sizeof(MAT4_IDENTITY));
	 

	 AddRenderComponent(&rc);
}
 
 void Update() {
	 glm_rotate_y(rc.Model,  0.1f, rc.Model);

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
 }