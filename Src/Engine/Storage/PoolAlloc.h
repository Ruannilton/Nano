#ifndef NANO_POOL_ALLOC
#define NANO_POOL_ALLOC

#include "MemoryManagerUtils.h"

struct ll_no
{
    uint used;
    struct ll_no* next;
    struct ll_no* prev;
    ptr block;
    uint id;
};

typedef struct  ll_no LinkedList_No;

typedef struct 
{
    LinkedList_No* first;
    LinkedList_No* last;
}LinkedList;

typedef struct 
{
    LinkedList_No* handler;
    ptr data;
}ChunkData;


typedef struct 
{
    LinkedList* manager;
    uint chunk_size;
    uint chunk_count;
    uint chunk_used;
    uint head_size;
    ptr chunks;
}PoolAllocator;

PoolAllocator* PoolAllocator_Create(uint chunk_size,uint chunk_count){  
    PoolAllocator* alloc = (PoolAllocator*) malloc(sizeof(PoolAllocator));
    alloc->manager = (LinkedList*)malloc(sizeof(LinkedList));

    alloc->chunks = malloc((chunk_size+sizeof(LinkedList_No*))*chunk_count);
    
    alloc->manager->first = (LinkedList_No*)malloc(sizeof(LinkedList_No)*chunk_count);
    LinkedList_No* current_no; 
    
    uint block_size = (chunk_size+sizeof(LinkedList_No*));
    
    register int i=0;
    for(;i<chunk_count;i++){
        
        uint s = (uint)(alloc->chunks) +(i* block_size);

        current_no = alloc->manager->first+i;
        current_no->block = (ChunkData*)s;
        ((ChunkData*)s)->handler = current_no;
        current_no->used = 0;
        current_no->id = i;

        printf("%d block in %d\n",i,s);
        
        if(i<chunk_count-1){
            current_no->prev = current_no-1;
            current_no->next = current_no+1;
        }else if(i==0){
            current_no->prev = 0;
            current_no->next = current_no+1;
        }
        else{
            current_no->next = 0;
            current_no->prev = current_no-1;
        }
    }

    alloc->manager->last = current_no;
    alloc->chunk_count = chunk_count;
    alloc->chunk_size = chunk_size;
    alloc->chunk_used = 0;
    alloc->head_size = sizeof(LinkedList_No*);

    return alloc;
}

ptr PoolAllocator_Next(PoolAllocator* alloc,ptr pointer){
    return (uint)pointer+alloc->chunk_size+alloc->head_size;
}

ptr PoolAllocator_Alloc(PoolAllocator* alloc){
    if(alloc->chunk_used == alloc->chunk_count) return 0;
    if(alloc->manager->first->used) return 0;

    ptr loc = ((uint)(alloc->manager->first->block)+sizeof(LinkedList_No*));
    LinkedList_No* tmp;
    alloc->manager->first->used = 1;
    alloc->manager->first->prev = alloc->manager->last;
    alloc->manager->last->next = alloc->manager->first;
    tmp = alloc->manager->first;
    alloc->manager->first = alloc->manager->first->next;
    alloc->manager->last =  tmp;
    tmp->next = 0;
    alloc->chunk_used++;
    return loc;
}

void PoolAllocator_Free(PoolAllocator* alloc,ptr pointer){
    LinkedList_No** header = ((uint)pointer - sizeof(LinkedList_No*));
    LinkedList_No* tmp = alloc->manager->first;
    
    if((*header) == alloc->manager->last){
        alloc->manager->last = (*header)->prev;
        alloc->manager->last->next = 0;
    }else{
        (*header)->prev->next = (*header)->next;
        (*header)->next->prev = (*header)->prev;
    }
   
    alloc->manager->first = *header;
    alloc->manager->first->next = tmp;
    tmp->prev = alloc->manager->first;
    alloc->manager->first->prev = 0;
    alloc->manager->first->used = 0;   
}

void PoolAllocator_PrintManager(PoolAllocator* alloc){
   LinkedList_No* tmp = alloc->manager->first;
   printf("Manager Order: ");
   while (tmp!=0)
   {
      printf(" %d ->",tmp->id);
      tmp = tmp->next;
   }
   printf("\n");
}
#endif