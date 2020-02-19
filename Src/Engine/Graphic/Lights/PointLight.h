#ifndef NANO_POINT_LIGHT
#define NANO_POINT_LIGHT

#include "../GL.h"
#include "../../Utils.h"
#include "../Shader.h"

typedef struct {
	Vec3 Ambient;
	Vec3 Diffuse;
	Vec3 Specular;
	Vec3 Position;
	Vec3 Color;
	//Attenuation vec3 on GPU
	float Constant;		// x
	float Linear;		// y
	float Quadratic;	// z
}PointLight;


inline PointLight* PointLight_CTR(PointLight* self, Vec3 Ambient, Vec3 Diffuse, Vec3 Specular, Vec3 Position, float Constant, float Linear,float Quadratic) {
	self->Ambient = Ambient;
	self->Diffuse = Diffuse;
	self->Specular = Specular;
	self->Position = Position;

	self->Constant = Constant;
	self->Linear = Linear;
	self->Quadratic = Quadratic;
	
	return self;
}

inline void PointLight_Bind(Shader shader, PointLight* light) {
	Shader_SetVec3(shader, "point_light.Position", light->Position.arr);
	Shader_SetVec3(shader, "point_light.Ambient", light->Ambient.arr);
	Shader_SetVec3(shader, "point_light.Diffuse", light->Diffuse.arr);
	Shader_SetVec3(shader, "point_light.Specular", light->Specular.arr);

	Shader_SetFloat(shader, "point_light.Constant", light->Constant);
	Shader_SetFloat(shader, "point_light.Linear", light->Linear);
	Shader_SetFloat(shader, "point_light.Quadratic", light->Quadratic);
}

#endif // ! NANO_LIGHT
