#include "StaticScene.h"

PointLight* StaticScene_Add_PointLight(StaticScene* self, Vec3 Position) {
	uint i;
	PointLight* pl = Vector_Add(&self->point_lights, &i);
	pl->Position = Position;
	pl->Ambient = (Vec3){ 0.4f,0.4f,0.4f };
	pl->Diffuse = (Vec3){ 0.5f,0.5f,0.5f };
	pl->Specular = (Vec3){ 1.0f,1.0f,1.0f };
	pl->Constant = 1.0f;
	pl->Linear = 0.045f;
	pl->Quadratic = 0.0075f;
	return pl;
}

SpotLight* StaticScene_Add_SpotLight(StaticScene* self, Vec3 Position, Vec3 Direction) {
	uint i;
	SpotLight* sl = Vector_Add(&self->spot_lights, &i);
	sl->Position = Position;
	sl->Direction = Direction;
	sl->Ambient = (Vec3){ 0.4f,0.4f,0.4f };
	sl->Diffuse = (Vec3){ 0.5f,0.5f,0.5f };
	sl->Specular = (Vec3){ 1.0f,1.0f,1.0f };
	sl->Constant = 1.0f;
	sl->Linear = 0.045f;
	sl->Quadratic = 0.0075f;
	sl->cutOff = 12.5f;
	sl->outerCutOff = 17.5f;
	return sl;
}