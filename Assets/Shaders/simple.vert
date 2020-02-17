#version 430

layout(std140, binding = 0) uniform Matrices
{
	mat4 projection;
	mat4 view;
};

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

layout (location = 4) uniform mat4 model;

out vec4 ourColor;

void main()
{
    gl_Position =projection*view*model*vec4(aPos, 1.0);
	ourColor = aColor;
}