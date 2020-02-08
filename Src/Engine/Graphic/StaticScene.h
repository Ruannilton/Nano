#ifndef NANO_STATIC_SCENE
#define NANO_STATIC_SCENE

#include "../DataStructures/Vector.h"
#include "Lights/Light.h"

typedef struct {
	DirectionalLight directional_light;
	Vector point_lights;
	Vector spot_lights;
	
}StaticScene;

inline StaticScene* StaticScene_CTR(StaticScene* self, int point_light_count, int spot_light_count) {
	Vector_CTR(&self->point_lights, sizeof(PointLight), point_light_count);
	Vector_CTR(&self->point_lights, sizeof(SpotLight), spot_light_count);
}

PointLight* StaticScene_Add_PointLight(StaticScene* self, Vec3 Position);
SpotLight*  StaticScene_Add_SpotLight (StaticScene* self, Vec3 Position,Vec3 Direction);

#endif // !NANO_SCENE
