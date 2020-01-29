#pragma once


#include "GL.h"
#include "..//Utils.h"
#include "Shader.h"

#define Material_CreateBindFnc(MATERIAL_NAME) void MATERIAL_NAME ## bndFnc (GLuint shader, void* data)
#define Material_GetBindFnc(MATERIAL_NAME) MATERIAL_NAME ## bndFnc
typedef void (*BindFnc)(GLuint shader, void* data);

struct _Material {
	Shader shader_id;
	BindFnc fnc;
	void* data;
};


typedef struct _Material Material;


inline Material* Material_CTR (Material* self, Shader shader, BindFnc bindFnc, void* data) {

	self->data = data;
	self->fnc = bindFnc;
	self->shader_id = shader;
	return self;
}




