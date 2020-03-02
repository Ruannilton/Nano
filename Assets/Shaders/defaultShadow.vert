#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 4) in mat4 aInstancedModel;

layout (location = 10) uniform mat4 lightSpaceMatrix;

void main(){
	gl_Position = lightSpaceMatrix*aInstancedModel*vec4(aPos, 1.0);
}