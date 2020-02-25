#ifndef NANO_CUBE_MAP
#define NANO_CUBE_MAP

#include "../Utils.h"
#include <SOIL2/SOIL2.h>

typedef struct {
	uint id;
}CubeMap;


CubeMap* CubeMap_LoadTexture(const char** path, GLenum wrapMode, GLenum minFilter, GLenum magFilter);
CubeMap* CubeMap_LoadTextureDefault(const char** path);
#endif // NANO_CUBE_MAP
