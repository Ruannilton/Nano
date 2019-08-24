#include "RenderComponent.h"

RenderComponent* RenderComponent_Create(Mesh* mesh, Material* mat) {
	static mat4 identity = GLM_MAT4_IDENTITY_INIT;
	RenderComponent* cmp = NEW(RenderComponent);
	cmp->mat = mat;
	cmp->mesh = mesh;
	memcpy(cmp->transform, identity, sizeof(identity));
}

void RenderComponent_SetMaterialData(RenderComponent* rc, void* data) {
	rc->mat->data = data;
}