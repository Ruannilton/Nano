#ifndef NANO_RENDER_COMPONENT
#define NANO_RENDER_COMPONENT

#include "GL.h"
#include <string.h>
#include "Material.h"
#include "Mesh.h"

#define RC_SetPosition RenderComponent_SetPosition

typedef struct {
	Mesh* mesh;
	Material* mat;
	mat4 transform;
}RenderComponent;


inline RenderComponent* RenderComponent_Create(Mesh* mesh, Material* mat) {
	static mat4 identity = GLM_MAT4_IDENTITY_INIT;
	RenderComponent* cmp = NEW(RenderComponent);
	VERIFY(cmp, NULL);
	cmp->mat = mat;
	cmp->mesh = mesh;
	memcpy(cmp->transform, identity, sizeof(identity));
	return cmp;
}

inline void RenderComponent_SetMaterialData(RenderComponent* rc, void* data) {
	rc->mat->data = data;
}

inline void RenderComponent_SetPosition(RenderComponent* rc, vec3 pos) {
	glm_translate(rc->transform, pos);
}

#endif // !NANO_RENDER_COMPONENT












