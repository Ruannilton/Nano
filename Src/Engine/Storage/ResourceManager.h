#ifndef NANO_RESOURCE_MANAGER
#define NANO_RESOURCE_MANAGER

#include "../Graphic/Mesh.h"
#include "../Graphic/Texture.h"
#include "../Graphic/Shader/Shader.h"
#include "../Utils.h"



Texture resources_textures[20];
Mesh resources_meshs[20];
NanoShader resources_shaders[20];

uint texCount = 0;
uint meshCount = 0;
uint shaderCount = 0;

__inline void ResourceManager_Init() {
	
}

__inline Texture* manager_LoadTexture(string path,uint* textureIndex) {
	//Texture* tex = (Texture*)malloc(sizeof(Texture));
	 texture_LoadTextureDefault(&resources_textures[texCount],path);
	 *textureIndex = texCount;
	 texCount++;
	 return &resources_textures[*textureIndex];
}

__inline Mesh* manager_LoadMesh(string path, uint* meshIndex) {
	//Mesh* mesh = (Mesh*)malloc(sizeof(Mesh));
	mesh_LoadMesh(&resources_meshs[meshCount],path);
	*meshIndex = meshCount;
	meshCount++;
	return &resources_meshs[*meshIndex];
}

__inline NanoShader* manager_LoadShader(string vs, string fs, uint* shaderIndex) {
	resources_shaders[shaderCount] = shader_LoadFromFile(vs, fs);
	*shaderIndex = shaderCount;
	shaderCount++;
	return &resources_shaders[*shaderIndex];
}
#endif