#ifndef NANO_HASH_MAP
#define NANO_HASH_MAP

#include <stdlib.h>
#include <stdio.h>

#define Dictionary(KEY,TYPE) Dictionary
#define Dictionary_Create(TYPE, SIZE,HASHF) internal_hash_map_create(SIZE, sizeof(TYPE) * 10,HASHF)
#define Dictionary_Get(TYPE, HASH_MAP, KEY) (TYPE *)internal_hash_map_get(HASH_MAP, KEY)
#define Dictionary_Add(TYPE, HASH_MAP, KEY) (TYPE *)internal_hash_map_add(HASH_MAP, KEY)

typedef unsigned int uint;
typedef uint (*hash_fnc)(uint size, void *data);

typedef struct
{
    uint data_size;
    uint count;
    uint size;
    uint *key_arr;
    void *data_arr;
    hash_fnc hash;

} Dictionary;

typedef struct {
    Dictionary* dic;
    void* data;
    uint key;
    uint current;
}Dic_Iterator;

uint default_hash(uint size, void *data);

Dictionary internal_hash_map_create(uint size, uint data_size, hash_fnc hash_f);

int Dictionary_ContainsKey(Dictionary *hm, void *key);

void *internal_hash_map_get(Dictionary *hm, void *key);

void *internal_hash_map_add(Dictionary *hm, void *key);

void *Dictionary_GetIndex(Dictionary *hm, uint i);

Dic_Iterator Dic_Iterator_Get(Dictionary* dic);

uint Dic_Iterator_Next(Dic_Iterator* iter);

void Dic_Iterator_Restar(Dic_Iterator* iter);

#endif