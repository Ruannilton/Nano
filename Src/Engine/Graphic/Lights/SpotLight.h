#ifndef  NANO_SPOT_LIGHT
#define  NANO_SPOT_LIGHT

#include "../GL.h"
#include "../../Utils.h"
#include "../Shader.h"


typedef struct {
	Vec3 Ambient;
	Vec3 Diffuse;
	Vec3 Specular;
	Vec3 Direction;
	Vec3 Position;

	//Attenuation vec3 on GPU
	float Constant;		// x
	float Linear;		// y
	float Quadratic;	// z

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

inline void SpotLight_Bind(Shader shader, SpotLight* light) {
	Shader_SetVec3(shader, "spot_light.Position", light->Position.arr);
	Shader_SetVec3(shader, "spot_light.Direction", light->Direction.arr);
	Shader_SetVec3(shader, "spot_light.Ambient", light->Ambient.arr);
	Shader_SetVec3(shader, "spot_light.Diffuse", light->Diffuse.arr);
	Shader_SetVec3(shader, "spot_light.Specular", light->Specular.arr);

	Shader_SetFloat(shader, "spot_light.Constant", light->Constant);
	Shader_SetFloat(shader, "spot_light.Linear", light->Linear);
	Shader_SetFloat(shader, "spot_light.Quadratic", light->Quadratic);
	Shader_SetFloat(shader, "spot_light.cutOff", (float)cos(glm_rad(light->cutOff)));
	Shader_SetFloat(shader, "spot_light.outerCutOff", (float)cos(glm_rad(light->outerCutOff)));
}

#endif // ! NANO_SPOT_LIGHT
