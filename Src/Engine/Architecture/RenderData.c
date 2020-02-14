#include "RenderData.h"


uint hash_f(uint size, void* data) {
	uint id = (uint)data;
	return id % size;
}


