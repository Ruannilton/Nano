
#ifndef TEXTURED_MATERIAL
#define TEXTURED_MATERIAL

#include "..//Engine/Graphic/Material.h"
#include "..//Engine/Graphic/Texture.h"


typedef struct {
	Texture* texture;
}TexturedMaterial;

Material_CreateBindFnc(TexturedMaterial) {
	Shader_SetTexture(((TexturedMaterial*)data)->texture->id);
	vec3 ambient = { 0.05375f,0.05f,0.06625f };
	vec3 diffuse = { 0.18275f,0.17f,0.63f };
	vec3 specular = { 0.332741f,0.328634f,0.346435f };


	Shader_SetVec3(shader, "material.Ambient", ambient);
	Shader_SetVec3(shader, "material.Diffuse", diffuse);
	Shader_SetVec3(shader, "material.Specular", specular);
	Shader_SetFloat(shader, "material.Shininess", 0.3f*128);

	Shader_SetVec3(shader, "CameraPos", currentCamera.position);
	Light_Bind(shader, &SceneLight);
	
}


inline Material* TexturedMaterial_CTR(TexturedMaterial* self,Shader shader, string file) {
	self->texture = texture_LoadTextureDefault(file);
	Material* mat = CNEW(Material, shader, TexturedMaterialbndFnc,self);
	return mat;
}

#endif