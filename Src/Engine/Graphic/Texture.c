#include "Texture.h"
#include <SOIL2/SOIL2.h>
#include "../Utils.h"


Texture* Texture_LoadTexture(const char* path, GLenum wrapMode, GLenum minFilter, GLenum magFilter) {
	Texture* tex = (Texture*)malloc(sizeof(Texture));
	VERIFY(tex, NULL);

	tex->id = SOIL_load_OGL_texture(path, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS);

	if (tex->id == 0)
	{
		DEBUG_C(ANSI_RED, "%s", "Failed to load texture");
		printf("%s\n", SOIL_last_result());
		return NULL;
	}

	glBindTexture(GL_TEXTURE_2D, tex->id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	glBindTexture(GL_TEXTURE_2D, 0);

	DEBUG_C(ANSI_LIGHT_GREEN, "Loaded Texture(%d): %s",tex->id, path);
	
	return tex;
}

Texture* Texture_LoadTextureDefault(const char* path) {
	return Texture_LoadTexture(path, DEFAULT_WRAP, DEFAULT_MIN_FILTER, DEFAULT_MAG_FILTER);
}