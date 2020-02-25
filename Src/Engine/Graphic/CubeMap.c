#include "CubeMap.h"

CubeMap* CubeMap_LoadTexture(const char** path, GLenum wrapMode, GLenum minFilter, GLenum magFilter) {
	CubeMap* cm = (CubeMap*)NEW(CubeMap);
	const char* right = path[0];
	const char* left = path[1];
	const char* top = path[2];
	const char* bottom = path[3];
	const char* front = path[4];
	const char* back = path[5];

	if (cm) {
		glActiveTexture(GL_TEXTURE0);
		cm->id = SOIL_load_OGL_cubemap(right, left, top, bottom, front, back, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cm->id);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, magFilter);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, minFilter);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, wrapMode);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, wrapMode);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, wrapMode);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return cm;
	}
	return NULL;
}
CubeMap* CubeMap_LoadTextureDefault(const char** path) {
	return CubeMap_LoadTexture(path, GL_CLAMP_TO_EDGE, GL_LINEAR, GL_LINEAR);
}