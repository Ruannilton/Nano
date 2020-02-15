#ifndef NANO_DYNAMIC_VECTOR
#define NANO_DYNAMIC_VECTOR

#include <stdlib.h>
#include <stdio.h>

typedef unsigned int uint;
typedef int (*map_fnc)(void *data);

#define Vector_Push(TYPE, VEC_PTR, INDEX_PTR) (TYPE *)internal_vector_push(VEC_PTR, INDEX_PTR)
#define Vector_Create(TYPE, SIZE) internal_create_vector(SIZE, sizeof(TYPE))
#define Vector_Get(TYPE, VEC_PTR, INDEX) (TYPE *)internal_vector_get(VEC_PTR, INDEX)
#define Vector_Remove(TYPE, VEC_PTR, INDEX) (TYPE *)internal_vector_remove(VEC_PTR, INDEX)

typedef struct
{
    size_t data_size;
    uint count;
    uint size;
    uint free_ptr;
    float grow_factor;
    void *buffer;
    uint *free_index;
} Vector;

typedef struct
{
    Vector *vec;
    uint current;
    uint rev_current;
    void *data;
} Iterator;

Vector internal_create_vector(uint size, size_t data_size);

void *internal_vector_push(Vector *self, uint *index_added);

void vector_resize(Vector *self, size_t new_size);

void *internal_vector_get(Vector *self, uint index);

void *internal_vector_remove(Vector *self, uint index);

int Vector_Join(Vector *dst, Vector *other);

void Vector_Clear(Vector *self);

void Vector_Delete(Vector *self);

Iterator Iterator_Get(Vector *vec);

int Iterator_Next(Iterator *it);

int Iterator_Reverse(Iterator *it);

int Iterator_Map(Iterator *it, map_fnc fnc);

void Iterator_Restart(Iterator *it);

#endif