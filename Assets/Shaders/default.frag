#version 430 core

out vec4 FragColor;
  
in vec2 TexCoord;
in vec3 ourColor;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord);
}