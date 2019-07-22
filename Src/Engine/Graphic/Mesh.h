#ifndef NANO_MESH
#define NANO_MESH

#include "../Utils.h"
#include "../Core/NanoIO.h"
#include "../GL.h"

#define STATIC_FLAG 1
#define POSITION_FLAG 2
#define COLOR_FLAG 4
#define NORMAL_FLAG 8
#define UV_FLAG 16

typedef struct {
	float* vertex;
	unsigned int* index;
	
	unsigned int flag;
	unsigned int vertexSize = 0;
	unsigned int vertexCount;
	unsigned int indexCount;
}Mesh;

void mesh_calculateVertexSize(Mesh* mesh) {
	mesh->vertexSize = 0;
	if (mesh->flag & POSITION_FLAG) mesh->vertexSize += 3;
	if (mesh->flag & COLOR_FLAG) mesh->vertexSize += 3;
	if (mesh->flag & NORMAL_FLAG) mesh->vertexSize += 3;
	if (mesh->flag & UV_FLAG) mesh->vertexSize += 2;
}

void mesh_LoadMesh(string path, Mesh* mesh) {

}

Mesh* mesh_BuildMesh(unsigned int* index,float* vertex,unsigned int flags,int indexCount,int vertexCount) {
	Mesh* mesh = NEW(Mesh);
	mesh->index = index;
	mesh->vertex = vertex;
	mesh->flag = flags;
	mesh->indexCount = indexCount;
	mesh->vertexCount = vertexCount;
	mesh_calculateVertexSize(mesh);
	return mesh;
}

GLuint mesh_genVAO(Mesh* mesh) {
	GLuint vbo;
	GLuint ebo;
	GLuint vao;
	unsigned int count = 0;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);


	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indexCount * sizeof(float), mesh->index, GL_STATIC_DRAW);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, mesh->vertexCount * sizeof(float), mesh->vertex, GL_STATIC_DRAW);



	if (mesh->flag & POSITION_FLAG) {
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, mesh->vertexSize * sizeof(float), (void*)(count * sizeof(float)));
		count += 3;
	}
	if (mesh->flag & COLOR_FLAG) {
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, mesh->vertexSize * sizeof(float), (void*)(count * sizeof(float)));
		count += 3;
	}
	if (mesh->flag & NORMAL_FLAG) {
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, mesh->vertexSize * sizeof(float), (void*)(count * sizeof(float)));
		count += 3;
	}
	if (mesh->flag & UV_FLAG) {
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, mesh->vertexSize * sizeof(float), (void*)(count * sizeof(float)));
		count += 2;
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return vao;
}

__inline void mesh_EnableFlags(Mesh* m, unsigned int flags) {
	m->flag |= flags;
}
__inline void mesh_DisableFlags(Mesh* m, unsigned int flags) {
	m->flag ^= flags;
}

#endif // !NANO_MESH
