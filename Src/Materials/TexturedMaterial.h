
#ifndef TEXTURED_MATERIAL
#define TEXTURED_MATERIAL

#include "..//Engine/Graphic/Material.h"
#include "..//Engine/Graphic/Texture.h"



typedef struct {
	Texture* texture;
	Texture* difffuse;
	Texture* specular;
}TexturedMaterial;

Material_CreateBindFnc(TexturedMaterial) {
	
	
	Shader_SetInt(shader, "ourTexture", 0);
	Shader_SetTextureUnit(((TexturedMaterial*)data)->texture->id, GL_TEXTURE0);

	Shader_SetInt(shader, "material.diffuse", 1);
	Shader_SetTextureUnit(((TexturedMaterial*)data)->difffuse->id,GL_TEXTURE1);

	Shader_SetInt(shader, "material.specular", 2);
	Shader_SetTextureUnit(((TexturedMaterial*)data)->specular->id, GL_TEXTURE2);

	Shader_SetFloat(shader, "material.Shininess", 32.0f);

	Shader_SetVec3(shader, "CameraPos", currentCamera.position);
	//DirectionalLight_Bind(shader, &Directional);
	//PointLight_Bind(shader, &SceneLight);
	SpotLight_Bind(shader, &spotLight);
}


inline Material* TexturedMaterial_CTR(TexturedMaterial* self,Shader shader, Texture* texture, Texture* diffuse, Texture* specular) {
	self->texture = texture;
	self->difffuse = diffuse;
	self->specular = specular;
	Material* mat = CNEW(Material, shader, TexturedMaterialbndFnc,self);
	return mat;
}

#endif