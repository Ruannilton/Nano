#ifndef NANO_MESH
#define NANO_MESH

#include "../Utils.h"
#include "GL.h"
#include "../Core/NanoIO.h"
#include "../DataStructures/dynamic_vector.h"

#define STATIC_FLAG 1
#define POSITION_FLAG 2
#define COLOR_FLAG 4
#define NORMAL_FLAG 8
#define UV_FLAG 16

#define PRIMITIVE_PLANE 1
#define PRIMITIVE_CUBE 2

UNIQUE  ulint mesh_loader_pre_alloc = 512;


typedef struct {
	Vec3 pos;
	Vec2 uv;
	Vec3 normal;
	Vec4 color;
}Vertex;

typedef struct {
	Vertex vert1, vert2, vert3;
}Face;

typedef struct {
	
	Vec3* vertices;
	uint* index;
	Vec2* uvs;
	Vec4* colors;
	Vec3* normals;

	uint vertices_count;
	uint index_count;
	uint uv_count;
	uint color_count;
	uint normal_count;
	uint mesh_id;
}Mesh;



GLuint mesh_genVAO(Mesh* mesh);
Mesh* mesh_LoadMesh(string path);
Mesh* mesh_LoadPrimitive(uint primitive);

void mesh_PrintMesh(Mesh* mesh);

CTR(Mesh) {
	return self;
}

#endif // !NANO_MESH

