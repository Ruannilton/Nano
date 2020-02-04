#version 430 core

struct Material{
	sampler2D diffuse;
	sampler2D specular;
	float Shininess;
};

struct Light{
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
	vec3 Position;
};

in vec2 TexCoord;
in vec4 ourColor;
in vec3 FragPos;
in vec3 Normal;


uniform vec3 CameraPos;
uniform sampler2D ourTexture;
uniform Light light;
uniform Material material;

out vec4 FragColor;

void main()
{

	
	vec3 texDiffuse = vec3(texture(material.diffuse, TexCoord));

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.Position - FragPos);
	float diff = max(dot(norm,lightDir),0.0);
		
	vec3 viewDir = normalize(CameraPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(0,dot(viewDir, reflectDir)), material.Shininess);
	

	vec3 ambient  = light.Ambient  * texDiffuse;
	vec3 diffuse  = light.Diffuse  * diff * texDiffuse;
	vec3 specular = light.Specular * spec * vec3(texture(material.specular, TexCoord));

	vec4 lightRes = vec4( ambient + diffuse+specular,1.0);

    FragColor = lightRes;
}