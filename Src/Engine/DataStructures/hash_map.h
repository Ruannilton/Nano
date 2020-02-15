#ifndef NANO_HASH_MAP
#define NANO_HASH_MAP

#include <stdlib.h>
#include <stdio.h>

#define Dictionary(KEY,TYPE) Dictionary
#define Dictionary_Create(TYPE, SIZE) internal_hash_map_create(SIZE, sizeof(TYPE) * 10)
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

uint default_hash(uint size, void *data);

Dictionary internal_hash_map_create(uint size, uint data_size);

int Dictionary_ContainsKey(Dictionary *hm, void *key);

void *internal_hash_map_get(Dictionary *hm, void *key);

void *internal_hash_map_add(Dictionary *hm, void *key);

void *Dictionary_GetIndex(Dictionary *hm, uint i);
#endif