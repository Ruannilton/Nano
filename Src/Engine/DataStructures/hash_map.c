#include "hash_map.h"

uint default_hash(uint size, void *data)
{
    size_t num = ((size_t)data);
    num %= (size - 1);
    return 1 + num;
}

hash_map internal_hash_map_create(uint size, uint data_size)
{
    size++; 
    hash_map h = {data_size, 0, size, (uint *)malloc(sizeof(uint) * size), malloc(data_size * size), default_hash};
    int i = 0;
    for (; i < size; i++)
        h.key_arr[i] = 0;
    return h;
}

int hash_map_contains(hash_map *hm, void *key)
{
    uint k = hm->hash(hm->size, key);
    return hm->key_arr[k];
}

void *internal_hash_map_get(hash_map *hm, void *key)
{
    uint k = hash_map_contains(hm, key);
    if (k)
    {
        return get_index(hm, k);
    }
    return NULL;
}

void *internal_hash_map_add(hash_map *hm, void *key)
{
   
    uint k = hm->hash(hm->size, key);
    hm->key_arr[k] = k;
    hm->count++;
    return get_index(hm, k);
}

void *get_index(hash_map *hm, uint i)
{
    return (void *)((size_t)hm->data_arr + (i * hm->data_size));
}
