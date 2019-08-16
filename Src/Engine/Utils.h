#ifndef NANO_UTILS
#define NANO_UTILS

#include <stdio.h>
#include <stdlib.h>
#define NEW(TYPE) (TYPE*)malloc(sizeof(TYPE))
#define DEBUG(STR) printf(STR##"\n");
#define SIZEVEC(VECTOR) sizeof(VECTOR) / sizeof(VECTOR[0])
#define REPEAT(I) for(int i=0;i<I;i++) 
#define kbyte(VALUE) 1024*VALUE
#define mbyte(VALUE) 1024*kbyte(VALUE)

typedef const char* string;
typedef unsigned int uint;
#endif // !NANO_UTILS

