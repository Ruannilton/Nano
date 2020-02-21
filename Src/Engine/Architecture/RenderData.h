#ifndef NANO_RENDER_TABLE
#define NANO_RENDER_TABLE
	
#include "InstanceList.h"
#include "../DataStructures/hash_map.h"
#include "../Graphic/RenderComponent.h"
#define Mesh_ID uint

uint hash_f(uint size, void* data);

typedef struct {
	Dictionary(Mesh_ID,InstanceList) renderer_lists;
	Dictionary(Mesh_ID, MultipleInstanceList) multiple_renderer_lists;
}RenderData;




#endif