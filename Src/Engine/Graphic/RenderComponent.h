#ifndef NANO_RENDER_COMPONENT
#define NANO_RENDER_COMPONENT

#include "../Utils.h"
#include <string.h>
#include "Material.h"
#include "Mesh.h"

#define RC_SetPosition RenderComponent_SetPosition

typedef struct {
	
	Material mat;
	mat4 transform;
}RenderComponent;

typedef struct {

	Material* mat;
	Vector* transforms;
}SharedRenderComponent;

inline void RenderComponent_SetPosition(RenderComponent* rc, Vec3 pos) {
	glm_translate(rc->transform, pos.arr);
}

inline void RenderComponent_SetMaterial(RenderComponent* rc, Material* mat) {
	memcpy(&rc->mat, mat, sizeof(Material));
}

inline void RenderComponent_Scale(RenderComponent* rc, Vec3 scale) {
	glm_scale(rc->transform, scale.arr);
}

inline void RenderComponent_Rotate(RenderComponent* rc, Vec3 rot) {
	glm_rotate(rc->transform, glm_rad(rot.x), X_Axis);
	glm_rotate(rc->transform, glm_rad(rot.y), Y_Axis);
	glm_rotate(rc->transform, glm_rad(rot.z), Z_Axis);
}
#endif // !NANO_RENDER_COMPONENT












