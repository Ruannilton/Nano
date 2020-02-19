#ifndef NANO_DIRECTIONAL
#define NANO_DIRECTIONAL

#include "../GL.h"
#include "../../Utils.h"
#include "../Shader.h"

typedef struct {
	Vec3 Ambient;
	Vec3 Diffuse;
	Vec3 Specular;
	Vec3 Direction;
	Vec3 Color;
}DirectionalLight;

inline DirectionalLight* DirectionalLight_CTR(DirectionalLight* self, Vec3 Direction, Vec3 Ambient, Vec3 Diffuse, Vec3 Specular) {
	self->Direction = Direction;
	self->Ambient = Ambient;
	self->Diffuse = Diffuse;
	self->Specular = Specular;
	return self;
}

inline void DirectionalLight_Bind(Shader shader, DirectionalLight* direction) {
	Shader_SetVec3(shader, "directional_light.Direction", direction->Direction.arr);
	Shader_SetVec3(shader, "directional_light.Ambient", direction->Ambient.arr);
	Shader_SetVec3(shader, "directional_light.Diffuse", direction->Diffuse.arr);
	Shader_SetVec3(shader, "directional_light.Specular", direction->Specular.arr);
}

#endif // !NANO_DIRECTIONAL
