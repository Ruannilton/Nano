#ifndef NANO_MATERIAL
#define NANO_MATERIAL

#include "GL.h"
#include "..//Utils.h"
#include "Shader.h"

#define Material_CreateBindFnc(MATERIAL_NAME) void MATERIAL_NAME ## bndFnc (GLuint shader, void* data)
#define Material_GetBindFnc(MATERIAL_NAME) MATERIAL_NAME ## bndFnc
typedef void (*BindFnc)(GLuint shader, void* data);

typedef struct {
	Shader shader_id;
	BindFnc fnc;
	void* data;
} Material;


inline Material* Material_CTR(Material* self, Shader shader, BindFnc bindFnc, void* data) {

	self->data = data;
	self->fnc = bindFnc;
	self->shader_id = shader;
	return self;
}


#endif // !NANO_MATERIAL




