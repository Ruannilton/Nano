#ifndef  NANO_SPOT_LIGHT
#define  NANO_SPOT_LIGHT

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
	Vec3 Direction;
	//cutOff vec2 on GPU
	float cutOff;		// x
	float outerCutOff;	// y
}SpotLight;


inline SpotLight* SpotLight_CTR(SpotLight* self, Vec3 Position, Vec3 Direction, float cutOff, float outerCutOff) {
	
	self->Position = Position;
	self->Direction = Direction;
	self->cutOff = cutOff;
	self->outerCutOff = outerCutOff;

	SetVec3(self->Ambient, 0.4f, 0.4f, 0.4f);
	SetVec3(self->Diffuse, 0.5f, 0.5f, 0.5f);
	SetVec3(self->Specular, 1, 1, 1);

	self->Constant = 1.0f;
	self->Linear = 0.045f;
	self->Quadratic = 0.0075f;
	return self;
}



#endif // ! NANO_SPOT_LIGHT
