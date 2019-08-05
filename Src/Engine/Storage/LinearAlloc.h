#ifndef NANO_LINEAR_ALLOC
#define NANO_LINEAR_ALLOC

#include "stdio.h"
#include "MemoryManagerUtils.h"

typedef struct{
    size_t lenght;
    unsigned int current;
    unsigned int end;
    unsigned int start;
} LinearAllocator;


LinearAllocator*  LinearAllocator_CreateAlloc(size_t l){
    LinearAllocator* alloc;
    alloc = (LinearAllocator*)malloc(sizeof(LinearAllocator));
    alloc->lenght = l;
    alloc->start =(unsigned int)malloc(l);
    alloc->current = alloc->start;
    alloc->end = alloc->start+l;
  return alloc;
}

ptr LinearAllocator_Alloc(LinearAllocator* alloc, size_t size){
    if(size+alloc->current > alloc->end) return 0;
    ptr loc = (ptr)alloc->current;
    alloc->current = alloc->current+size;
    return loc; 
}

__inline void LinearAllocator_Clear(LinearAllocator* alloc){
    alloc->current = alloc->start;
}

void LinearAllocator_Free(LinearAllocator* alloc){
    free((void*)alloc->start);
    free(alloc);
}

#endif