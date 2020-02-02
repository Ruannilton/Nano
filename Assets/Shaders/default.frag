#version 430 core

out vec4 FragColor;
  
in vec2 TexCoord;
in vec3 ourColor;

uniform sampler2D ourTexture;
layout (location = 7) uniform vec3 AmbientLight;
layout (location = 8) uniform float AmbientIntensity;

void main()
{
    FragColor = texture(ourTexture, TexCoord) * vec4(AmbientLight, 1.0) *AmbientIntensity;
}