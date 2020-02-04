#version 430 core

struct Material{
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
	float Shininess;
};

struct Light{
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
	vec3 Position;
};
  
in vec4 ourColor;
in vec3 FragPos;
in vec3 Normal;


uniform vec3 CameraPos;
uniform Light light;
uniform Material material;
uniform vec4 color;

out vec4 FragColor;

void main()
{

	vec3 ambient = light.Ambient * material.Ambient;

	//difuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.Position - FragPos);
	float diff = max(dot(norm,lightDir),0.0);
	vec3 diffuse = light.Diffuse * (material.Diffuse * diff);

	//specular
	vec3 viewDir = normalize(CameraPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(0,dot(viewDir, reflectDir)), material.Shininess);
	vec3 specular = light.Specular * (material.Specular*spec);

	vec4 lightRes = vec4( ambient + diffuse+specular,1.0);

    FragColor = lightRes * ourColor* color;
}