#ifndef NANO_LINEAR_MEMORY
#define NANO_LINEAR_MEMORY

#include <malloc.h>

#define kbyte(VALUE) 1024*VALUE
#define mbyte(VALUE) 1024*kbyte(VALUE)

#define DEF_VECTOR(TYPE) typedef struct { TYPE* data; unsigned int lenght; unsigned int index; }Vector_##TYPE;
#define VECTOR_NEW(TYPE) Vector_##TYPE* Create_Vector_##TYPE(unsigned int lenght){ Vector_##TYPE* v = (Vector_##TYPE*)malloc(sizeof(Vector_##TYPE)); v->data = (TYPE*)malloc(lenght*sizeof(TYPE));v->lenght = lenght;v->index=0;}
#define VECTOR_STORE(TYPE) void Store_Vector_##TYPE(TYPE* value)
DEF_VECTOR(int);
VECTOR_NEW(int);
#endif // !NANO_LINEAR_MEMORY