#ifndef NANO_SKYBOX
#define NANO_SKYBOX

#include "../Utils.h"
#include "Shader.h"
#include "CubeMap.h"

UNIQUE uint skybox_vao;

typedef struct {
	Shader shader;
	CubeMap texture;
}Skybox;


Skybox* Skybox_Create(Shader shader, CubeMap texture);

void Skybox_Init();

void Skybox_Use(Skybox* sky);

#endif