#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

layout (location = 4) uniform mat4 model;
layout (location = 5) uniform mat4 view;
layout (location = 6) uniform mat4 projection;

out vec3 ourColor;
out vec2 TexCoord;


void main()
{
    gl_Position = projection*view*model*vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}