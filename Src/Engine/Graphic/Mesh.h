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


int mesh_loader_pre_alloc = (int)(kbyte(0.5f));


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

	FILE* file;
	fopen_s(&file, path, "r");
	char desc[3];
	
	unsigned int vert_count = 0;
	unsigned int index_count = 0;
	unsigned int norm_count = 0;
	unsigned int uv_count = 0;
	unsigned int vertSize = 3;
	unsigned int i;

	vec3* vertList = (vec3*)malloc(sizeof(vec3*) * (mesh_loader_pre_alloc+1));
	vec3* normList = (vec3*)malloc(sizeof(vec3*) * (mesh_loader_pre_alloc+1));
	vec2* uvList   = (vec2*)malloc(sizeof(vec2*) * (mesh_loader_pre_alloc+1));
	vec3* faceList = (vec3*)malloc(sizeof(vec3*) * (9*(mesh_loader_pre_alloc+1)));
	
	float* mesh_verts;
	unsigned int* mesh_index;
	int index_perline = 0;

	#pragma region READ FILE
	while (!feof(file))
	{
		if (fscanf_s(file,"%s", &desc)) {

			if (strcmp(desc, "v") == 0) {
				vert_count += 1;
				fscanf_s(file, "%f %f %f", &vertList[vert_count][0], &vertList[vert_count][1], &vertList[vert_count][2]);
			}
			else if (strcmp(desc, "vn") == 0) {
				norm_count += 1;
				fscanf_s(file, "%f %f %f", &normList[norm_count][0], &normList[norm_count][1], &normList[norm_count][2]);
			}
			else if (strcmp(desc, "vt") == 0) {
				uv_count += 1;
				fscanf_s(file, "%f %f", &uvList[uv_count][0], &uvList[uv_count][1]);
			}
			else if (strcmp(desc, "f") == 0) {

				int vert1, tex1, norm1, vert2, tex2, norm2, vert3, tex3, norm3;

				if (uv_count == 0 && norm_count == 0) {
					int matches = fscanf_s(file, "%d %d %d", &vert1, &vert2, &vert3);
					tex1 = norm1 = -1;
					tex2 = norm2 = -1;
					tex3 = norm3 = -1;
				}
				else if (uv_count == 0) {
					int matches = fscanf_s(file, " %d//%d %d//%d %d//%d", &vert1, &norm1, &vert2, &norm2, &vert3, &norm3);
					tex1 = -1;
					tex2 = -1;
					tex3 = -1;
				}
				else if (norm_count == 0) {
					int matches = fscanf_s(file, "%d/%d %d/%d %d/%d", &vert1, &tex1, &vert2, &norm2, &vert3, &norm3);
					norm1 = -1;
					norm2 = -1;
					norm3 = -1;
				}
				else {
					int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d", &vert1, &tex1, &norm1, &vert2, &tex2, &norm2, &vert3, &tex3, &norm3);				
				}

				faceList [index_count][0] = (float)(vert1);
				faceList [index_count + 1][0] = (float)(vert2);
				faceList [index_count + 2][0] = (float)(vert3);
				faceList [index_count][1] = (float)(tex1);
				faceList [index_count + 1][1] = (float)(tex2);
				faceList [index_count + 2][1] = (float)(tex3);
				faceList [index_count][2] = (float)(norm1);
				faceList [index_count + 1][2] = (float)(norm2);
				faceList [index_count + 2][2] = (float)(norm3);
				index_count += 3;
			}
		}
	}
#pragma endregion

	mesh->flag = POSITION_FLAG;
	
	if (uv_count != 0) {
		mesh->flag |= UV_FLAG;
		vertSize += 2;
	}
	if (norm_count != 0) {
		mesh->flag |= NORMAL_FLAG;
		vertSize += 3;
	}

	mesh_verts = (float*)malloc(sizeof(float) * (vertSize * index_count));
	mesh_index = (unsigned int*)malloc(sizeof(unsigned int) * index_count);
	mesh->vertexCount = vertSize*index_count;
	mesh->indexCount = index_count;
	mesh->vertexSize = vertSize;
	
	unsigned int verti = 0;
	int iv, in, it;
	float v1, v2, v3, t1, t2, n1, n2, n3;
	
	for (i = 0; i < index_count; i++) {

		mesh_index[i] = i;


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
