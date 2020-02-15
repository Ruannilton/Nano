#include "dynamic_vector.h"

Vector internal_create_vector(uint size, size_t data_size)
{
    if (size <= 1)
        size = 2;
    Vector v;
    v.buffer = malloc(size * data_size);
    v.free_index = (uint *)malloc(size * sizeof(uint));
    v.count = 0;
    v.free_ptr = 0;
    v.size = size;
    v.data_size = data_size;
    v.grow_factor = 0.5f;
    return v;
}

void *internal_vector_get(Vector *self, uint index)
{
    size_t ptr = (size_t)self->buffer;
    return (void *)(ptr + (index * self->data_size));
}

void vector_resize(Vector *self, size_t new_size)
{
    void *ptr = self->buffer;
    void *free_ind = self->free_index;
    self->size = new_size;

    self->buffer = realloc(ptr, new_size * self->data_size);
    self->free_index = (uint *)realloc(free_ind, new_size * self->data_size);
}

void *internal_vector_push(Vector *self, uint *index_added)
{
    uint index = self->count;

    if (self->free_ptr)
        index = self->free_index[--self->free_ptr];
    else
    {
        while (self->count >= self->size)
        {
            vector_resize(self, (size_t)(self->size * (1 + self->grow_factor)));
        }
        self->count++;
    }

    size_t ptr = (size_t)self->buffer;

    if (index_added)
        *index_added = index;

    return (void *)(ptr + (index * self->data_size));
}

int Vector_Join(Vector *dst, Vector *other)
{
    if (dst->data_size != other->data_size)
        return 0;

    uint free_space = dst->size - dst->count;
    if (free_space < other->count)
    {
        vector_resize(dst, (other->count - free_space));
    }

    Iterator it = Iterator_Get(other);
    while (Iterator_Next(&it))
    {
        char *ptr = (char *)internal_vector_push(dst, NULL);
        char *cpy = (char *)it.data;
        register int i = 0;
        for (; i < other->data_size; i++)
        {
            ptr[i] = cpy[i];
        }
    }
    return 1;
}

void Vector_Clear(Vector *self)
{
    self->count = 0;
}

void *internal_vector_remove(Vector *self, uint index)
{
    self->free_index[self->free_ptr++] = index;
    size_t ptr = ((size_t)self->buffer + (self->data_size * index));
    return (void *)ptr;
}

void Vector_Delete(Vector *self)
{
    free(self->buffer);
    free(self);
}

Iterator Iterator_Get(Vector *vec)
{
    Iterator i;
    i.vec = vec;
    i.current = 0;
    i.rev_current = vec->count;
    return i;
}

int Iterator_Next(Iterator *it)
{
    if (it->current == it->vec->count)
    {
        return 0;
    }

    do
    {
        it->data = (void *)((it->current * it->vec->data_size) + (size_t)it->vec->buffer);
        it->current++;
    } while (it->data == NULL);
    return 1;
}
int Iterator_Reverse(Iterator *it)
{
    if (it->rev_current == 0)
        return 0;
    do
    {
        if (it->rev_current == 0)
            return 0;
        it->rev_current--;
        it->data = (void *)((it->rev_current * it->vec->data_size) + (size_t)it->vec->buffer);
    } while (it->data == NULL);

    return 1;
}
int Iterator_Map(Iterator *it, map_fnc fnc)
{
    if (it->current == it->vec->size)
    {
        return 0;
    }
    do
    {
        if (it->current == it->vec->size)
            return 0;
        it->data = (void *)((it->current * it->vec->data_size) + (size_t)it->vec->buffer);
        it->current++;
    } while (!fnc(it->data));
    return 1;
}

void Iterator_Restart(Iterator *it)
{
    it->current = 0;
    it->rev_current = it->vec->count;
}