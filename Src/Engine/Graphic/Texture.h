#ifndef NANO_TEXTURE
#define NANO_TEXTURE


#include "../GL.h"
#define STB_IMAGE_IMPLEMENTATION
#include <STB/stb_image.h>
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

Texture* texture_LoadTexture(const char* path, GLenum wrapMode, GLenum minFilter, GLenum magFilter) {
	Texture* tex = (Texture*)malloc(sizeof(Texture));

	glGenTextures(1, &tex->id);
	glBindTexture(GL_TEXTURE_2D, tex->id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);


	unsigned char* data = stbi_load(path, &tex->widht, &tex->height, &tex->channels, 0);
	
	if (data)
	{
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->widht, tex->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("%s\n", "Failed to load texture");
		return NULL;
	}
	stbi_image_free(data);
	return tex;
}

Texture* texture_LoadTextureDefault(const char* path) {
	return texture_LoadTexture(path, DEFAULT_WRAP, DEFAULT_MIN_FILTER, DEFAULT_MAG_FILTER);
}
#endif // !_nano_texture_
