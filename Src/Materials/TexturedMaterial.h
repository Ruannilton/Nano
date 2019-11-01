
#ifndef TEXTURED_MATERIAL
#define TEXTURED_MATERIAL

#include "..//Engine/Graphic/Material.h"
#include "..//Engine/Graphic/Texture.h"


typedef struct {
	Texture* texture;
}TexturedMaterial;

Material_CreateBindFnc(TexturedMaterial) {
	glBindTexture(shader, ((TexturedMaterial*)data)->texture->id);
}


#endif