#include "InstanceList.h"

InstanceList* InstanceList_Create(InstanceList* il,uint vao, uint init_size) {
	il->mesh_id = vao;
	il->instances = Vector_Create(RenderComponent, init_size);
	return il;
}

MultipleInstanceList* MultipleInstanceList_Create(MultipleInstanceList* il, uint vao, Material* mat, uint init_size) {
	il->mesh_id = vao;
	il->instances = Vector_Create(mat4, init_size);
	memcpy(&il->material, mat, sizeof(Material));
	return il;
}