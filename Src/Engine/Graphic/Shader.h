#ifndef NANO_SHADER
#define NANO_SHADER

#include "GL.h"
#include "../Utils.h"
#include <string.h>
#include "../Core/NanoIO.h"

typedef GLuint Shader;


unsigned int shader_CompileShader(string src, GLenum type);
Shader shader_CreateShader(string vs, string fs);

__inline void Shader_SetTexture(uint texID) {
	glBindTexture(GL_TEXTURE_2D, texID);
}

__inline void Shader_SetTextureUnit(uint texID, GLenum unit) {
	glActiveTexture(unit);
	glBindTexture(GL_TEXTURE_2D, texID);
}

__inline void Shader_SetFloat(Shader shader,string local, float value) {
	glUniform1f(glGetUniformLocation(shader, local), value);
}

__inline void Shader_SetVec2(Shader shader, string local, float* value) {
	glUniform2fv(glGetUniformLocation(shader, local), 1,value);
}

__inline void Shader_SetVec3(Shader shader, string local, float* value) {
	glUniform3fv(glGetUniformLocation(shader, local), 1, value);
}

__inline void Shader_SetVec4(Shader shader, string local, float* value) {
	glUniform4fv(glGetUniformLocation(shader, local), 1, value);
}
#endif // !NANO_SHADER





