#ifndef NANO_RENDER_COMPONENT
#define NANO_RENDER_COMPONENT

#include "GL.h"
#include <string.h>
#include "Material.h"
#include "Mesh.h"

typedef struct {
	Mesh* mesh;
	Material* mat;
	mat4 transform;
}RenderComponent;


RenderComponent* RenderComponent_Create(Mesh* mesh, Material* mat);
void RenderComponent_SetMaterialData(RenderComponent* rc, void* data);

#endif // !NANO_RENDER_COMPONENT












