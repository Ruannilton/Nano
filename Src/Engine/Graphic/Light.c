#include "Light.h"

void Light_Bind(Shader shader, Light* light) {
	Shader_SetVec3(shader, "light.Position", light->Position.arr);
	Shader_SetVec3(shader, "light.Ambient", light->Ambient.arr);
	Shader_SetVec3(shader, "light.Diffuse", light->Diffuse.arr);
	Shader_SetVec3(shader, "light.Specular", light->Specular.arr);
}