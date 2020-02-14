#include "dynamic_vector.h"

dynamic_vector internal_create_vector(uint size, size_t data_size)
{
    if (size <= 1)
        size = 2;
    dynamic_vector v;
    v.buffer = malloc(size * data_size);
    v.free_index = (uint *)malloc(size * sizeof(uint));
    v.count = 0;
    v.free_ptr = 0;
    v.size = size;
    v.data_size = data_size;
    v.grow_factor = 0.5f;
    return v;
}

void *internal_vector_get(dynamic_vector *self, uint index)
{
    size_t ptr = (size_t)self->buffer;
    return (void *)(ptr + (index * self->data_size));
}

void vector_resize(dynamic_vector *self, size_t new_size)
{
    void *ptr = self->buffer;
    void *free_ind = self->free_index;
    self->size = new_size;

    self->buffer = realloc(ptr, new_size * self->data_size);
    self->free_index = (uint *)realloc(free_ind, new_size * self->data_size);
}

void *internal_vector_push(dynamic_vector *self, uint *index_added)
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

int vector_join(dynamic_vector *dst, dynamic_vector *other)
{
    if (dst->data_size != other->data_size)
        return 0;

    uint free_space = dst->size - dst->count;
    if (free_space < other->count)
    {
        vector_resize(dst, (other->count - free_space));
    }

    iterator it = get_iterator(other);
    while (iterator_next(&it))
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

void vector_clear(dynamic_vector *self)
{
    self->count = 0;
}

void *internal_vector_remove(dynamic_vector *self, uint index)
{
    self->free_index[self->free_ptr++] = index;
    size_t ptr = ((size_t)self->buffer + (self->data_size * index));
    return (void *)ptr;
}

void vector_delete(dynamic_vector *self)
{
    free(self->buffer);
    free(self);
}

iterator get_iterator(dynamic_vector *vec)
{
    iterator i;
    i.vec = vec;
    i.current = 0;
    i.rev_current = vec->count;
    return i;
}

int iterator_next(iterator *it)
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
int iterator_reverse(iterator *it)
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
int iterator_map(iterator *it, map_fnc fnc)
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

void iterator_restart(iterator *it)
{
    it->current = 0;
    it->rev_current = it->vec->count;
}