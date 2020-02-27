#include "TexturedMaterial.h"

Material_CreateBindFnc(TexturedMaterial) {

	TexturedMaterial* tex = data;

	Shader_SetInt(shader, "material.diffuse", 0);
	Shader_SetTextureUnit(tex->difffuse->id, GL_TEXTURE0);

	Shader_SetInt(shader, "material.specular", 1);
	Shader_SetTextureUnit(tex->specular->id, GL_TEXTURE1);

	Shader_SetFloat(shader, "material.Shininess", 32.0f);

}