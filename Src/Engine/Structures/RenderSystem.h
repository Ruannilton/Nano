#pragma once

#include "..//Graphic/Rendering/Material.h"
#include "..//Components/RenderComponent.h"

#define SHADER_UNIFORM_MODEL 5
#define SHADER_UNIFORM_VIEW 6
#define SHADER_UNIFORM_PROJECTION 7

typedef struct _Mesh_Instance Mesh_Instance;
typedef struct _Meshs_Instances Meshs_Instances;
typedef struct _Materials_Instances Materials_Instances;

struct _Mesh_Instance {
	mat4* transform;
	Mesh_Instance* prox;
};

struct _Meshs_Instances {
	GLuint mesh_id;
	Mesh_Instance* instances;
	Meshs_Instances* prox;
};

struct _Materials_Instances {
	Material material;
	Meshs_Instances* meshs;
};

typedef struct RenderStructure{
	Materials_Instances* render_data;
};

void Render_AddComponent(RenderComponent* rc) {

}

