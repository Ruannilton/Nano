#ifndef NANO_DYNAMIC_VECTOR
#define NANO_DYNAMIC_VECTOR

#include <stdlib.h>
#include <stdio.h>

typedef unsigned int uint;
typedef int (*map_fnc)(void *data);

#define vector_push(TYPE, VEC_PTR, INDEX_PTR) (TYPE *)internal_vector_push(VEC_PTR, INDEX_PTR)
#define vector_create(TYPE, SIZE) internal_create_vector(SIZE, sizeof(TYPE))
#define vector_get(TYPE, VEC_PTR, INDEX) (TYPE *)internal_vector_get(VEC_PTR, INDEX)
#define vector_remove(TYPE, VEC_PTR, INDEX) (TYPE *)internal_vector_remove(VEC_PTR, INDEX)

typedef struct
{
    size_t data_size;
    uint count;
    uint size;
    uint free_ptr;
    float grow_factor;
    void *buffer;
    uint *free_index;
} dynamic_vector;

typedef struct
{
    dynamic_vector *vec;
    uint current;
    uint rev_current;
    void *data;
} iterator;

dynamic_vector internal_create_vector(uint size, size_t data_size);

void *internal_vector_push(dynamic_vector *self, uint *index_added);

void vector_resize(dynamic_vector *self, size_t new_size);

void *internal_vector_get(dynamic_vector *self, uint index);

void *internal_vector_remove(dynamic_vector *self, uint index);

int vector_join(dynamic_vector *dst, dynamic_vector *other);

void vector_clear(dynamic_vector *self);

void vector_delete(dynamic_vector *self);

iterator get_iterator(dynamic_vector *vec);

int iterator_next(iterator *it);

int iterator_reverse(iterator *it);

int iterator_map(iterator *it, map_fnc fnc);

void iterator_restart(iterator *it);

#endif