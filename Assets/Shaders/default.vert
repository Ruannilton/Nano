#version 430 core

layout(std140, binding = 0) uniform Matrices
{
	mat4 projection;
	mat4 view;
};

layout(std140, binding = 2) uniform Models
{
	mat4 models[1024];
};

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

out vec4 ourColor;
out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;

void main()
{
    gl_Position =projection*view*models[gl_InstanceID]*vec4(aPos, 1.0);
    TexCoord = aTexCoord;
	ourColor = aColor;
	FragPos = vec3(models[gl_InstanceID]*vec4(aPos, 1.0));
	Normal = mat3(transpose(inverse(models[gl_InstanceID]))) * aNormal;
}