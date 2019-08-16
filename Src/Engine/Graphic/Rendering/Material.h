#pragma once


#include "..//..//GL.h"
#include "..//..//Utils.h"
#include "Shader.h"

typedef void (*MaterialDataFnc)(GLuint shader, void* data);

struct _Material {
	Shader shader_id;
	MaterialDataFnc fnc;
};

typedef struct _Material Material;


struct ReflexMat {
	int tex;
	float bri;
};

void ReflexFNC(GLuint shader, void* data) {
	ReflexMat* dat = (ReflexMat*)data;
}
