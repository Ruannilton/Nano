#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
//#include <STB/stb_image.h>
#include <SOIL2/SOIL2.h>
#include "../Utils.h"


Texture* texture_LoadTexture(const char* path, GLenum wrapMode, GLenum minFilter, GLenum magFilter) {
	Texture* tex = (Texture*)malloc(sizeof(Texture));
	
	tex->id = SOIL_load_OGL_texture(path, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	if (tex->id == 0)
	{
		printf("%s\n", "Failed to load texture");
		return NULL;
	}

	glBindTexture(GL_TEXTURE_2D, tex->id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	return tex;
}

Texture* texture_LoadTextureDefault(const char* path) {
	return texture_LoadTexture(path, DEFAULT_WRAP, DEFAULT_MIN_FILTER, DEFAULT_MAG_FILTER);
}