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
	float* vertex;
	unsigned int* index;
	GLuint mesh_id;
	unsigned int flag;
	unsigned int vertexSize;
	unsigned int vertexCount;
	unsigned int indexCount;
}Mesh;


GLuint mesh_genVAO(Mesh* mesh);

Mesh* mesh_LoadMesh(string path);
Mesh* mesh_BuildMesh(unsigned int* index, float* vertex, unsigned int flags, int indexCount, int vertexCount);

void mesh_PrintMesh(Mesh* mesh);
void mesh_calculateVertexSize(Mesh* mesh);


__inline void mesh_EnableFlags(Mesh* m, unsigned int flags) {
	m->flag |= flags;
}
__inline void mesh_DisableFlags(Mesh* m, unsigned int flags) {
	m->flag ^= flags;
}
#endif // !NANO_MESH

