#ifndef NANO_SHADER
#define NANO_SHDAER

#include "../GL.h"
#include "../Utils.h"
#include <string.h>

typedef struct 
{
	GLuint ID;
	GLuint modelLoc;
	GLuint viewLoc;
	GLuint projectionLoc;
} Shader;

unsigned int shader_CompileShader(string src, GLenum type) {
	GLuint id = glCreateShader(type);
	glShaderSource(id, 1, &src, NULL );
	glCompileShader(id);

	int res;
	glGetShaderiv(id, GL_COMPILE_STATUS, &res);

	if (!res) {
		int len = 256;
		char log[256];
		glGetShaderInfoLog(id, len, &len, log);
		printf("ERROR COMPILE %s SHADER:\n%s", (type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT", log);
		glDeleteShader(id);
		return 0;
	}

	return id;
}

Shader shader_CreateShader(string vs, string fs) {
	
	Shader s;
	unsigned int prog = glCreateProgram();
	unsigned int vsID = 0;
	unsigned int fsID = 0;

	vsID = shader_CompileShader(vs,GL_VERTEX_SHADER);
	fsID = shader_CompileShader(fs,GL_FRAGMENT_SHADER);
	
	glAttachShader(prog, vsID);
	glAttachShader(prog, fsID);
	glLinkProgram(prog);
	glValidateProgram(prog);

	glDeleteShader(vsID);
	glDeleteShader(fsID);

	s.ID = prog;
	glUseProgram(prog);
	s.projectionLoc = glGetUniformLocation(prog, "projection");
	s.modelLoc = glGetUniformLocation(prog, "model");
	s.viewLoc = glGetUniformLocation(prog, "view");
	glUseProgram(0);

	return s;
}

#endif // !NANO_SHADER

