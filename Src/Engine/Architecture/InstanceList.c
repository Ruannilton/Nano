#include "InstanceList.h"

InstanceList* instance_list_create(InstanceList* il,uint vao, uint init_size) {
	il->mesh_id = vao;
	il->instances = vector_create(Instance, init_size);
	return il;
}