#ifndef NANO_MESH
#define NANO_MESH

#include "../Utils.h"
#include "GL.h"

#define STATIC_FLAG 1
#define POSITION_FLAG 2
#define COLOR_FLAG 4
#define NORMAL_FLAG 8
#define UV_FLAG 16

UNIQUE int mesh_loader_pre_alloc = kbyte(0.5);

typedef struct {
	float* vertices;
	uint* index;
	float* uvs;
	float* colors;
	float* normals;

	uint vertices_count;
	uint index_count;
	uint uv_count;
	uint color_count;
	uint normal_count;
	uint mesh_id;
}Mesh;



GLuint mesh_genVAO(Mesh* mesh);
Mesh* mesh_LoadMesh(string path);

void mesh_PrintMesh(Mesh* mesh);
void mesh_calculateVertexSize(Mesh* mesh);

#endif // !NANO_MESH

