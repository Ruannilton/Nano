#ifndef NANO_UTILS
#define NANO_UTILS

#include <stdio.h>
#include <stdlib.h>
#define NEW(TYPE) (TYPE*)malloc(sizeof(TYPE))
#define DEBUG(STR,...) printf("NANO> "##STR##"\n",##__VA_ARGS__);
#define SIZEVEC(VECTOR) sizeof(VECTOR) / sizeof(VECTOR[0])
#define REPEAT(I) for(int i=0;i<I;i++) 

typedef const char* string;
typedef unsigned int uint;
#endif // !NANO_UTILS

