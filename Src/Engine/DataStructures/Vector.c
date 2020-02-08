#include "Vector.h"

void* Vector_Add(Vector* self,uint* index_added) {
	
	if (self->count == self->lenght) {
		Vector_Resize(self, (int)(self->count * 1.5f));
	}

	uint index = self->count++;
	
	if (self->free_count) {
		index = self->free_index[--self->free_count];
	}
	size_t ptr = (size_t)self->buff;

	if(index_added !=NULL)*index_added = index;
	
	return (void*)(ptr + (index * self->data_size));
}

void Vector_Resize(Vector* self, uint new_size) {

	self->lenght += (int)(new_size);

	if (self->buff) {
		void* tmp = realloc(self->buff, self->lenght * self->data_size);
		self->buff = tmp;
	}
	VERIFY(self->buff, NULL);
}


void* Vector_Get(Vector* self, uint i) {
	if (i < 0 || i >= self->lenght) return NULL;
	return (void*)((size_t)self->buff + i * self->data_size);
}
