#ifndef NANO_RENDER_COMPONENT
#define NANO_RENDER_COMPONENT

#include "../GL.h"

typedef struct {
	GLuint Shader;
	GLuint Texture;
	GLuint Vao;
	unsigned int IndexCount;
	mat4 Model;
}RenderComponent;



#endif // !NANO_RENDER_COMPONENT
