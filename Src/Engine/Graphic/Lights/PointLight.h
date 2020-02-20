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
	//Attenuation vec3 on GPU
	float Constant;		// x
	float Linear;		// y
	float Quadratic;	// z
	Vec3 Color;
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


#endif // ! NANO_LIGHT
