#include "InstanceList.h"

InstanceList* InstanceList_Create(InstanceList* il,uint vao, uint init_size) {
	il->mesh_id = vao;
	il->instances = Vector_Create(Instance, init_size);
	return il;
}