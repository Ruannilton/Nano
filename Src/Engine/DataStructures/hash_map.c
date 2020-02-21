#include "hash_map.h"

uint default_hash(uint size, void *data)
{
    size_t num = ((size_t)data);
    num %= (size - 1);
    return 1 + num;
}

Dictionary internal_hash_map_create(uint size, uint data_size , hash_fnc hash_f)
{
    size++; 
    if (!hash_f) hash_f = default_hash;
    Dictionary h = {data_size, 0, size, (uint *)malloc(sizeof(uint) * size), malloc(data_size * size), hash_f };
    int i = 0;
    for (; i < size; i++)
        h.key_arr[i] = 0;
    return h;
}

int Dictionary_ContainsKey(Dictionary *hm, void *key)
{
    uint k = hm->hash(hm->size, key);
    return hm->key_arr[k];
}

void *internal_hash_map_get(Dictionary *hm, void *key)
{
    uint k = Dictionary_ContainsKey(hm, key);
    if (k)
    {
        return Dictionary_GetIndex(hm, k);
    }
    return NULL;
}

void *internal_hash_map_add(Dictionary *hm, void *key)
{
   
    uint k = hm->hash(hm->size, key);
    hm->key_arr[k] = k;
    hm->count++;
    return Dictionary_GetIndex(hm, k);
}

void *Dictionary_GetIndex(Dictionary *hm, uint i)
{
    return (void *)((size_t)hm->data_arr + (i * hm->data_size));
}

Dic_Iterator Dic_Iterator_Get(Dictionary* dic) {
    Dic_Iterator iter;
    iter.current = 0;
    iter.data = 0;
    iter.key = 0;
    iter.dic = dic;
    return iter;
}

uint Dic_Iterator_Next(Dic_Iterator* iter) {
    
    if (iter->current > iter->dic->count) return 0;

    do {
        iter->key = *(uint*)((iter->current * sizeof(uint)) + (size_t)iter->dic->key_arr);
        iter->data = Dictionary_Get(void, iter->dic, iter->key);
        iter->current++;
    } while (iter->data == NULL);

    return 1;
}

void Dic_Iterator_Restar(Dic_Iterator* iter) {
    iter->current = 0;
    iter->data = 0;
    iter->key = 0;
}