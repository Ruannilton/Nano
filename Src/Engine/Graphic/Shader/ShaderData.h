#ifndef NANO_SHADER_DATA
#define NANO_SHDAER_DATA

#include "..//..//Utils.h"
#include "..//..//GL.h"
#include "Shader.h"
typedef enum {
	GL_UNIFORM1F = 1,
	GL_UNIFORM2F,
	GL_UNIFORM2F,
	GL_UNIFORM4F,
	GL_UNIFORM1I,
	GL_UNIFORM2I,
	GL_UNIFORM2I,
	GL_UNIFORM4I,
	GL_UNIFORM1UI,
	GL_UNIFORM2UI,
	GL_UNIFORM2UI,
	GL_UNIFORM4UI,
	GL_UNIFORM1FV,
	GL_UNIFORM2FV,
	GL_UNIFORM2FV,
	GL_UNIFORM4FV,
	GL_UNIFORM1IV,
	GL_UNIFORM2IV,
	GL_UNIFORM2IV,
	GL_UNIFORM4IV,
	GL_UNIFORM1UIV,
	GL_UNIFORM2UIV,
	GL_UNIFORM2UIV,
	GL_UNIFORM4UIV,
	GL_UNIFORM_M2FV,
	GL_UNIFORM_M3FV,
	GL_UNIFORM_M4FV,
	GL_UNIFORM_M2_3FV,
	GL_UNIFORM_M3_2FV,
	GL_UNIFORM_M2_4FV,
	GL_UNIFORM_M4_2FV,
	GL_UNIFORM_M3_4FV,
	GL_UNIFORM_M4_3FV
}DATA_TYPE;


typedef struct ShaderData {
	GLuint dataID;
	DATA_TYPE TYPE;
	void* Data;
	ShaderData* prox;
};

void ShaderData_AddUniform(string name,NanoShader** shader,size_t size, DATA_TYPE data_type,void* data ) {
	ShaderData* dat = (ShaderData*)malloc(sizeof(GLuint)+sizeof(DATA_TYPE)+size+sizeof(ShaderData*));
	dat->dataID = glGetUniformLocation((*shader)->ID, name);
	dat->TYPE = data_type;
	memcpy(dat->Data, data,size);
	dat->prox = NULL;
}

#endif