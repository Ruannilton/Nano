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
}Light;


inline Light* Light_CTR(Light* self, Vec3 Ambient, Vec3 Diffuse, Vec3 Specular, Vec3 Position) {
	self->Ambient = Ambient;
	self->Diffuse = Diffuse;
	self->Specular = Specular;
	self->Position = Position;
	
	return self;
}

inline void Light_Bind(Shader shader, Light* light) {
	Shader_SetVec3(shader, "light.Position", light->Position.arr);
	Shader_SetVec3(shader, "light.Ambient", light->Ambient.arr);
	Shader_SetVec3(shader, "light.Diffuse", light->Diffuse.arr);
	Shader_SetVec3(shader, "light.Specular", light->Specular.arr);
}

#endif // ! NANO_LIGHT
