
#ifndef TEXTURED_MATERIAL
#define TEXTURED_MATERIAL

#include "..//Engine/Graphic/Material.h"
#include "..//Engine/Graphic/Texture.h"


typedef struct {
	Texture* texture;
}TexturedMaterial;

Material_CreateBindFnc(TexturedMaterial) {
	//printf("Binding texture %d on shader %d\n", ((TexturedMaterial*)data)->texture->id, shader);
	glBindTexture(shader, ((TexturedMaterial*)data)->texture->id);
}


#endif