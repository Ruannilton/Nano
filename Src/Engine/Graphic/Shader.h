#ifndef NANO_SHADER
#define NANO_SHADER

#include "GL.h"
#include "../Utils.h"
#include <string.h>

typedef GLuint Shader;


	unsigned int shader_CompileShader(string src, GLenum type);
	Shader shader_CreateShader(string vs, string fs);


#endif // !NANO_SHADER





