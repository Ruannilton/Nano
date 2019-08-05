#ifndef NANO_STACK_ALLOCATOR
#define NANO_STACK_ALLOCATOR

#include "MemoryManagerUtils.h"

struct header 
{
    struct header* prev;
};

typedef struct header Header; 

typedef struct{
    Header* lastAllock;
    ptr data;
    ptr index;
    ptr end;
}StackAllocator;

StackAllocator* StackAllocator_Creat(uint block_size,uint count){
    uint size = (block_size+sizeof(Header))*count;
    StackAllocator* alloc = (StackAllocator*)malloc(sizeof(Header*)+size);
    alloc->data = alloc+sizeof(Header*);
    alloc->index = alloc->data;
    alloc->lastAllock = 0;
    alloc->end = (ptr)((uint)alloc->data+size);
    printf("Header size: %u\n",sizeof(Header));
    return alloc;
}

ptr StackAllocator_Alloc(StackAllocator* alloc,uint size){
    uint final_size = size+sizeof(Header);
    if((uint)alloc->index+final_size > (uint)alloc->end) return 0;
    ptr loc = (ptr)((uint)alloc->index+sizeof(Header));

    ((Header*)alloc->index)->prev = alloc->lastAllock;
    alloc->lastAllock = ((Header*)alloc->index);
    alloc->index = (ptr)((uint)alloc->index+final_size);
    return loc;
}

void StackAllocator_Free(StackAllocator* alloc){
    alloc->index = alloc->lastAllock;
    alloc->lastAllock = alloc->lastAllock->prev;
}
#endif