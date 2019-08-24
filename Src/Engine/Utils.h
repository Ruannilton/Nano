#pragma once

#include <stdio.h>
#include <stdlib.h>

#define REPEAT_1(COUNT)                   for(int i=0;i <COUNT; i++)
#define REPEAT_2(VARNAME,COUNT)           for(int VARNAME=0;VARNAME <COUNT; VARNAME ++)
#define REPEAT_3(VARNAME,COUNT,STRIDE)    for(int VARNAME=0;VARNAME <COUNT; VARNAME +=STRIDE)

#define NEW(TYPE) (TYPE*)malloc(sizeof(TYPE))
#define DEBUG(STR,...) printf(STR##"\n",##__VA_ARGS__);
#define SIZEVEC(VECTOR) sizeof(VECTOR) / sizeof(VECTOR[0])
#define kbyte(VALUE) 1024*VALUE
#define mbyte(VALUE) 1024*kbyte(VALUE)
#define UNIQUE __declspec(selectany) 
#define ARRAY(TYPE,COUNT) (TYPE*)malloc(sizeof(TYPE)*COUNT)

typedef const char* string;
typedef unsigned int uint;
typedef unsigned long int ulint;

#define EXT_C extern "C" {
#define END_EXT_C }

#ifdef __cplusplus
#define EXT_C 
#define END_EXT_C 
#endif
