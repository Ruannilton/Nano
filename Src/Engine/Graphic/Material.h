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

#define Material_Create(ShaderType,Shader, Data) iMaterial_Create(Shader,Material_GetBindFnc(ShaderType),Data)

inline Material* iMaterial_Create(Shader shader, BindFnc bindFnc, void* data) {
	Material* m = NEW(Material);
	m->data = data;
	m->fnc = bindFnc;
	m->shader_id = shader;
	return m;
}




