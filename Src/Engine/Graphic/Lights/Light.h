#ifndef NANO_LIGHT
#define NANO_LIGHT

#include "../GL.h"
#include "../../Utils.h"
#include "../Shader.h"

typedef struct {
	Vec3 Ambient;
	Vec3 Diffuse;
	Vec3 Specular;
	Vec3 Position;

	float Constant;
	float Linear;
	float Quadratic;
}SpotLight;


inline SpotLight* Light_CTR(SpotLight* self, Vec3 Ambient, Vec3 Diffuse, Vec3 Specular, Vec3 Position, float Constant, float Linear,float Quadratic) {
	self->Ambient = Ambient;
	self->Diffuse = Diffuse;
	self->Specular = Specular;
	self->Position = Position;

	self->Constant = Constant;
	self->Linear = Linear;
	self->Quadratic = Quadratic;
	
	return self;
}

inline void Light_Bind(Shader shader, SpotLight* light) {
	Shader_SetVec3(shader, "light.Position", light->Position.arr);
	Shader_SetVec3(shader, "light.Ambient", light->Ambient.arr);
	Shader_SetVec3(shader, "light.Diffuse", light->Diffuse.arr);
	Shader_SetVec3(shader, "light.Specular", light->Specular.arr);

	Shader_SetFloat(shader, "light.Constant", light->Constant);
	Shader_SetFloat(shader, "light.Linear", light->Linear);
	Shader_SetFloat(shader, "light.Quadratic", light->Quadratic);
}

#endif // ! NANO_LIGHT
