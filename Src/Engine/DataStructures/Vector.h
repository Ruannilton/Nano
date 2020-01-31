#ifndef NANO_VECTOR
#define NANO_VECTOR

#include "../Utils.h"

typedef struct {
	uint lenght;
	uint count;
	size_t data_size;
	void* buff;
}Vector;

inline Vector* Vector_CTR(Vector* self,size_t data_size,uint initial_lenght) {
	self->buff = malloc(data_size * initial_lenght);
	self->count = 0;
	self->lenght = initial_lenght;
	self->data_size = data_size;
	return self;
}

void* Vector_Add(Vector* self,uint* index_added);
void* Vector_Get(Vector* self, uint i);

inline void* Vector_DEL(Vector* self) {
	free(self->buff);
	free(self);
}

#endif
