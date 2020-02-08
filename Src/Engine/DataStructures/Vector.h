#ifndef NANO_VECTOR
#define NANO_VECTOR

#include "../Utils.h"

typedef struct {
	uint lenght;
	uint count;
	uint free_count;
	uint free_last;
	size_t data_size;
	uint* free_index;
	void* buff;
}Vector;

inline Vector* Vector_CTR(Vector* self,size_t data_size,uint initial_lenght) {
	self->buff = ALLOC(data_size * initial_lenght);
	self->buff = ARRAY(uint, initial_lenght);
	self->count = 0;
	self->lenght = initial_lenght;
	self->data_size = data_size;
	return self;
}

inline void Vector_Remove(Vector* self, uint index) {
	self->free_index[self->free_count++] = index;
}

inline void* Vector_DEL(Vector* self) {
	free(self->buff);
	free(self);
}

void  Vector_Resize(Vector* self, uint new_size);
void* Vector_Add(Vector* self,uint* index_added);
void* Vector_Get(Vector* self, uint i);

#endif
