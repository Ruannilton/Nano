#pragma once

#include <stdio.h>
#include <stdlib.h>

#define ANSI_RED "\x1b[31m"

#define ANSI_GREEN "\x1b[32m"

#define ANSI_YELLOW "\x1b[33m"

#define ANSI_BLUE "\x1b[34m"

#define ANSI_MAGENTA "\x1b[35m"

#define ANSI_CYAN "\x1b[36m"

#define ANSI_RESET "\x1b[0m"

#define ANSI_WHITE "\033[01;37m"

#define ANSI_BLACK "\033[22;30m"

#define ANSI_LIGHT_RED "\033[01;31m"

#define ANSI_LIGHT_GREEN "\033[01;32m"

#define ANSI_LIGHT_BLUE "\033[01;34m"

#define REPEAT_1(COUNT)                   for(int i=0;i <COUNT; i++)
#define REPEAT_2(VARNAME,COUNT)           for(int VARNAME=0;VARNAME <COUNT; VARNAME ++)
#define REPEAT_3(VARNAME,COUNT,STRIDE)    for(int VARNAME=0;VARNAME <COUNT; VARNAME +=STRIDE)

#define NEW(TYPE) (TYPE*)malloc(sizeof(TYPE))
#define CNEW(TYPE,...) TYPE##_CTR(NEW(TYPE),##__VA_ARGS__)
#define CTR(TYPE) inline TYPE* TYPE##_CTR(TYPE* self)
#define DEL(TYPE,ptr) TYPE##_DEL(ptr)

#define DEBUG(STR,...) printf(ANSI_WHITE##STR##"\n",##__VA_ARGS__);
#define DEBUG_C(COLOR,STR,...) printf(COLOR##STR##"\n",##__VA_ARGS__);
#define SIZEVEC(VECTOR) sizeof(VECTOR) / sizeof(VECTOR[0])
#define UNIQUE __declspec(selectany) 
#define ARRAY(TYPE,COUNT) (TYPE*)malloc(sizeof(TYPE)*COUNT)
#define kbyte(VALUE) 1024*VALUE
#define mbyte(VALUE) 1024*kbyte(VALUE)

typedef const char* string;
typedef unsigned int uint;
typedef unsigned long int ulint;

#define EXT_C extern "C" {
#define END_EXT_C }

#ifdef __cplusplus
#define EXT_C 
#define END_EXT_C 
#endif
