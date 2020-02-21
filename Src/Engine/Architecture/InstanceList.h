#ifndef NANO_INSTANCE_TABLE
#define NANO_INSTANCE_TABLE


#include "../Utils.h"
#include "../Graphic/Material.h"
#include "../DataStructures/dynamic_vector.h"
#include "../DataStructures/hash_map.h"
#include "../Graphic/RenderComponent.h"


typedef struct {
	uint mesh_id;
	uint index_count;
	Vector instances;
}InstanceList;

typedef struct {
	uint mesh_id;
	uint index_count;
	Material material;
	Vector instances;
}MultipleInstanceList;

InstanceList* InstanceList_Create(InstanceList* il, uint vao, uint init_size);

MultipleInstanceList* MultipleInstanceList_Create(MultipleInstanceList* il, uint vao,Material* mat, uint init_size);

#endif