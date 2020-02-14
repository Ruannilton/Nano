#ifndef NANO_HASH_MAP
#define NANO_HASH_MAP

#include <stdlib.h>
#include <stdio.h>

#define HashMap(KEY,TYPE) hash_map
#define hash_map_create(TYPE, SIZE) internal_hash_map_create(SIZE, sizeof(TYPE) * 10)
#define hash_map_get(TYPE, HASH_MAP, KEY) (TYPE *)internal_hash_map_get(HASH_MAP, KEY)
#define hash_map_add(TYPE, HASH_MAP, KEY) (TYPE *)internal_hash_map_add(HASH_MAP, KEY)

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

} hash_map;

uint default_hash(uint size, void *data);

hash_map internal_hash_map_create(uint size, uint data_size);

int hash_map_contains(hash_map *hm, void *key);

void *internal_hash_map_get(hash_map *hm, void *key);

void *internal_hash_map_add(hash_map *hm, void *key);

void *get_index(hash_map *hm, uint i);
#endif