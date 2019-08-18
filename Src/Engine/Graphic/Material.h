#pragma once


#include "GL.h"
#include "..//Utils.h"
#include "Shader.h"

typedef void (*BindFnc)(GLuint shader, void* data);

struct _Material {
	Shader shader_id;
	BindFnc fnc;
	void* data;
};

typedef struct _Material Material;

