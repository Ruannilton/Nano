#ifndef NANO_MESH
#define NANO_MESH

#include "../Utils.h"
#include "../Core/NanoIO.h"

typedef struct {
	float vertex*;
	unsigned int index*;
	
	unsigned int flag;

	unsigned int vertexCount;
	unsigned int indexCount;
}Mesh;

void LoadMesh(string path, Mesh* mesh) {

}

#endif // !NANO_MESH
