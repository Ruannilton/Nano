
#ifndef NANO_TEXTURE
#define NANO_TEXTURE

#include "GL.h"
#include <stdio.h>




#define DEFAULT_WRAP GL_REPEAT
#define DEFAULT_MIN_FILTER GL_NEAREST_MIPMAP_NEAREST
#define DEFAULT_MAG_FILTER GL_NEAREST

typedef struct {
	unsigned int id;
	int widht;
	int height;
	int channels;
}Texture;

Texture* Texture_LoadTexture(const char* path, GLenum wrapMode, GLenum minFilter, GLenum magFilter);
Texture* Texture_LoadTextureDefault(const char* path);

#endif // !NANO_TEXTURE
