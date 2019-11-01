#include "LinkedTable.h"


LinkedTable* LinkedTable_Create(uint table_size) {

	Table* tb = NEW(Table);
	tb->isFull = false;
	tb->prev = NULL;
	tb->next = NULL;
	tb->data = ARRAY(int, table_size);
	tb->insertIn = -1;
	

	LinkedTable* lt = NEW(LinkedTable);
	lt->data = tb;
	lt->last_table = tb;
	lt->element_count = 0;
	lt->table_size = table_size;
	lt->table_count = 1;
	lt->element_size = sizeof(int);

	return lt;
 }

ptr LinkedTable_AtIndex(LinkedTable* lt, uint index) {
	uint tb_index = (index /lt->table_size);
	uint element_index = index % lt->table_size;
	Table* tb = lt->data;
	REPEAT_1(tb_index) {
		tb = tb->next;
	}
	return &tb->data[element_index];
}

uint LinkedTable_Add(LinkedTable* lt, uint value,ptr ref) {
	lt->last_table->data[lt->last_table->insertIn] = value;
}

void LinkedTable_Remove(LinkedTable* lt, uint index) {
	
}