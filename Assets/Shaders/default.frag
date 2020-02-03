#version 430 core

out vec4 FragColor;
  
in vec2 TexCoord;
in vec3 ourColor;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D ourTexture;

layout (location = 7) uniform vec3 AmbientLight;
layout (location = 8) uniform float AmbientIntensity;

layout (location = 9) uniform vec3 DiffuseLightPos;
layout (location = 10) uniform vec3 DiffuseLightColor;
layout (location = 11) uniform float DifusseIntensity;

void main()
{

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(DiffuseLightPos - FragPos);
	float diff = max(dot(norm,lightDir),0.0);

	vec3 diffuse = DiffuseLightColor * DifusseIntensity * diff;
	vec3 ambient = AmbientLight *AmbientIntensity;

	vec4 light = vec4(diffuse+ambient,1.0);

    FragColor = texture(ourTexture, TexCoord) * light;
}