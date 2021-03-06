#ifndef NANO_UTILS
#define NANO_UTILS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Windows
#include <direct.h>
#define GetCurrentDir _getcwd

#include "Graphic/GL.h"

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
#define ARRAY(TYPE,COUNT) (TYPE*)malloc(sizeof(TYPE)*COUNT)
#define CNEW(TYPE,...) TYPE##_CTR(NEW(TYPE),##__VA_ARGS__)
#define CTR(TYPE) inline TYPE* TYPE##_CTR(TYPE* self)
#define DEL(TYPE,ptr) TYPE##_DEL(ptr)
#define ALLOC(SIZE) malloc(SIZE);
#define DEBUG(STR,...) printf(ANSI_WHITE##STR##"\n",##__VA_ARGS__)
#define DEBUG_C(COLOR,STR,...) printf(COLOR##STR##"\n",##__VA_ARGS__)
#define NOT_ENOUGH_MEM(STR) DEBUG_C(ANSI_LIGHT_RED,"[ERROR] Fail to allocate memory: %s",STR)
#define VERIFY(PTR,RET) if(!PTR){ DEBUG_C(ANSI_LIGHT_RED,"[ERROR] Fail to allocate memory"); return RET; }
#define SIZEVEC(VECTOR) sizeof(VECTOR) / sizeof(VECTOR[0])
#define UNIQUE __declspec(selectany) 
#define KBYTE(VALUE) (uint)(1024*VALUE)
#define MBYTE(VALUE) (uint)(1024*KBYTE(VALUE))
#define true 1
#define false 0


typedef const char* string;
typedef unsigned int uint;
typedef unsigned long int ulint;

typedef union {
	vec4 arr;
	struct {
		float x, y, z, w;
	};
}Vec4;

typedef union {
	vec3 arr;
	struct {
		float x, y, z;
	};
}Vec3;

typedef union {
	vec2 arr;
	struct {
		float x, y;
	};
}Vec2;

#define SetVec2(VAR,X,Y)   VAR.x = X; \
						   VAR.y = Y; 
						  
#define SetVec3(VAR,X,Y,Z) VAR.x = X; \
						   VAR.y = Y; \
						   VAR.z = Z; 

#define SetVec4(VAR,X,Y,Z,W) VAR.x = X; \
						     VAR.y = Y; \
						     VAR.z = Z; \
							 VAR.w = W;

#define Vec3Sum(a,b) a.x += b.x;\
					 a.y += b.y;\
					 a.z += b.z;

#define Vec3Mul(a,b) a.x *= b;\
					 a.y *= b;\
					 a.z *= b;

#define Vec2Sum(a,b) a.x += b.x;\
					 a.y += b.y;

#define Vec2Mul(a,b) a.x *= b;\
					 a.y *= b;

UNIQUE float X_Axis[3] = { 1,0,0 };
UNIQUE float Y_Axis[3] = { 0,1,0 };
UNIQUE float Z_Axis[3] = { 0,0,1 };

UNIQUE mat4 identity = GLM_MAT4_IDENTITY_INIT;
#endif
