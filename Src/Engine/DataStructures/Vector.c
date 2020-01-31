#include "Vector.h"

void* Vector_Add(Vector* self,uint* index_added) {
	if (self->count == self->lenght) {
		self->lenght += (int)(self->lenght * 1.5f);
		DEBUG("Increasing: %d",self->lenght);
		self->buff = realloc(self->buff, self->lenght * self->data_size);
	}
	size_t ptr = self->buff;
	if(index_added !=NULL)index_added = self->count;
	size_t stride = self->count * self->data_size;
	self->count++;
	return (void*)(ptr + stride);
}

void* Vector_Get(Vector* self, uint i) {
	if (i < 0 || i >= self->lenght) return NULL;
	return (void*)((size_t)self->buff + i * self->data_size);
}
