#pragma once

#include <stdio.h>
#include <stdlib.h>
#define NEW(TYPE) (TYPE*)malloc(sizeof(TYPE))
#define DEBUG(STR) printf(STR##"\n");
#define SIZEVEC(VECTOR) sizeof(VECTOR) / sizeof(VECTOR[0])
#define REPEAT(VAR,I,STRIDE) for(int VAR=0;VAR <I; VAR +=STRIDE) 
#define kbyte(VALUE) 1024*VALUE
#define mbyte(VALUE) 1024*kbyte(VALUE)
#define UNIQUE __declspec(selectany) 
typedef const char* string;
typedef unsigned int uint;
typedef unsigned long int ulint;

#define EXT_C extern "C" {
#define END_EXT_C }

#ifdef __cplusplus
#define EXT_C 
#define END_EXT_C 
#endif
