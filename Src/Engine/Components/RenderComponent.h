#ifndef NANO_RENDER_COMPONENT
#define NANO_RENDER_COMPONENT

#include "../GL.h"
#include <string.h>



typedef struct {
	GLuint Shader;
	GLuint Texture;
	GLuint Vao;
	unsigned int IndexCount;
	mat4 Model;
}RenderComponent;

__inline void _RenderComponent(RenderComponent* rc, GLuint shader, GLuint texture, GLuint vao, unsigned int IndexCount) {
	mat4 identity = GLM_MAT4_IDENTITY_INIT;
	rc->IndexCount = IndexCount;
	rc->Shader = shader;
	rc->Texture = texture;
	rc->Vao = vao;
	memcpy(rc->Model, identity, sizeof(identity));
}

#endif // !NANO_RENDER_COMPONENT
