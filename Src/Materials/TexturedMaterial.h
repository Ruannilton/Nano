
#ifndef TEXTURED_MATERIAL
#define TEXTURED_MATERIAL

#include "..//Engine/Graphic/Material.h"
#include "..//Engine/Graphic/Texture.h"



typedef struct {
	Texture* texture;
	Texture* difffuse;
	Texture* specular;
}TexturedMaterial;

Material_CreateBindFnc(TexturedMaterial);

inline Material* TexturedMaterial_CTR(TexturedMaterial* self,Shader shader, Texture* texture, Texture* diffuse, Texture* specular) {
	self->texture = texture;
	self->difffuse = diffuse;
	self->specular = specular;
	Material* mat = CNEW(Material, shader, TexturedMaterialbndFnc,self);
	return mat;
}

#endif