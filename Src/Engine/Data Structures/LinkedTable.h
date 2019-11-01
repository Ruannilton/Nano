#ifndef NANO_LINKED_TABLE
#define NANO_LINKED_TABLE

#include "NanoDataStructures.h"
#include <math.h>

#define full_flag char
#define remove_flag char

#define true 'y'
#define false 'n'

#define FILL_WITH_END 'f'
#define ADD_TO_REMOVED_LIST 'a'

 struct _Table{
	full_flag isFull;
	uint insertIn;
	int* data;
	struct _Table* next;
	struct _Table* prev;
};

 typedef struct _Table Table;


 struct _NextIn
 {
	 Table* tb_pos;
	 uint index;
	 struct _NextIn* next;
 };

 typedef struct _NextIn NextIn;

 struct _LinkedTable
 {
	 uint table_size;
	 uint table_count;
	 uint element_count;
	 uint element_size;
	
	 Table* data;
	 Table* last_table;
 };

 typedef struct _LinkedTable LinkedTable;


 LinkedTable* LinkedTable_Create(uint table_size);
 uint LinkedTable_Add(LinkedTable* lt,uint value, ptr ref);
 ptr LinkedTable_AtIndex(LinkedTable* lt,uint index);
#endif // !NANO_LINKED_TABLE
