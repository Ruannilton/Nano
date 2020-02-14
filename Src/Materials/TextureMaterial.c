#include "TexturedMaterial.h"

Material_CreateBindFnc(TexturedMaterial) {


	Shader_SetInt(shader, "ourTexture", 0);
	Shader_SetTextureUnit(((TexturedMaterial*)data)->texture->id, GL_TEXTURE0);

	Shader_SetInt(shader, "material.diffuse", 1);
	Shader_SetTextureUnit(((TexturedMaterial*)data)->difffuse->id, GL_TEXTURE1);

	Shader_SetInt(shader, "material.specular", 2);
	Shader_SetTextureUnit(((TexturedMaterial*)data)->specular->id, GL_TEXTURE2);

	Shader_SetFloat(shader, "material.Shininess", 32.0f);

}