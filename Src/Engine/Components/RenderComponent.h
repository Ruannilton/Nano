#pragma once

#include "../GL.h"
#include <string.h>
#include "..//Graphic/Rendering/Material.h"
#include "..//Graphic/Mesh.h"

typedef void* MaterialData;


typedef struct {
	
	GLuint Mesh_ID;
	unsigned int IndexCount;
	mat4 transform;

	Material* mat;
	MaterialData matData;
}RenderComponent;

RenderComponent* RenderComponent_Create(Mesh* mesh, Material* mat, MaterialData dat) {
	static mat4 identity = GLM_MAT4_IDENTITY_INIT;
	RenderComponent* cmp = NEW(RenderComponent);
	cmp->IndexCount = mesh->indexCount;
	cmp->mat = mat;
	cmp->matData = dat;
	cmp->Mesh_ID = mesh->mesh_id;
	memcpy(cmp->transform, identity, sizeof(identity));
}


