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
} Vec_Iterator;

Vector internal_create_vector(uint size, size_t data_size);

void *internal_vector_push(Vector *self, uint *index_added);

void vector_resize(Vector *self, size_t new_size);

void *internal_vector_get(Vector *self, uint index);

void *internal_vector_remove(Vector *self, uint index);

int Vector_Join(Vector *dst, Vector *other);

void Vector_Clear(Vector *self);

void Vector_Delete(Vector *self);

Vec_Iterator Vec_Iterator_Get(Vector *vec);

int Vec_Iterator_Next(Vec_Iterator *it);

int Vec_Iterator_Reverse(Vec_Iterator *it);

int Vec_Iterator_Map(Vec_Iterator *it, map_fnc fnc);

void Vec_Iterator_Restart(Vec_Iterator *it);

#endif