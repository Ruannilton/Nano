
#ifndef TEXTURED_MATERIAL
#define TEXTURED_MATERIAL

#include "..//Engine/Graphic/Material.h"
#include "..//Engine/Graphic/Texture.h"


typedef struct {
	Texture* texture;
}TexturedMaterial;

Material_CreateBindFnc(TexturedMaterial) {
	glBindTexture(GL_TEXTURE_2D, ((TexturedMaterial*)data)->texture->id);
	
	glUniform3fv(7, 1, AmbientLight.arr);
	glUniform1f(8, (GLfloat)AmbientIntensity);

	glUniform3fv(9, 1, DiffusePos.arr);
	glUniform3fv(10, 1, DiffuseLight.arr);
	glUniform1f(11, (GLfloat)DiffuseIntensity);
}


inline Material* TexturedMaterial_CTR(TexturedMaterial* self,Shader shader, string file) {
	self->texture = texture_LoadTextureDefault(file);
	Material* mat = CNEW(Material, shader, TexturedMaterialbndFnc,self);
	return mat;
}

#endif