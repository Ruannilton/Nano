#include "Shader.h"

unsigned int Shader_CompileShader(string path,string src, GLenum type) {
	GLuint id = glCreateShader(type);
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);

	int res;
	glGetShaderiv(id, GL_COMPILE_STATUS, &res);

	if (!res) {
		int len = 256;
		char log[256];
		glGetShaderInfoLog(id, len, &len, log);
		DEBUG_C(ANSI_RED,"ERROR COMPILE %s SHADER:\nAt: %s\n%s", (type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT", path, log);
		glDeleteShader(id);
		return 0;
	}

	return id;
}

Shader Shader_CreateShader(string vs, string fs) {

	
	unsigned int prog = glCreateProgram();
	unsigned int vsID = 0;
	unsigned int fsID = 0;

	vsID = Shader_CompileShader(vs,IO_ReadFile(vs), GL_VERTEX_SHADER);
	fsID = Shader_CompileShader(fs,IO_ReadFile(fs), GL_FRAGMENT_SHADER);

	glAttachShader(prog, vsID);
	glAttachShader(prog, fsID);
	glLinkProgram(prog);
	glValidateProgram(prog);

	glDeleteShader(vsID);
	glDeleteShader(fsID);
	DEBUG_C(ANSI_LIGHT_GREEN, "SHADER(%d) LOADED", prog);
	return prog;
}

