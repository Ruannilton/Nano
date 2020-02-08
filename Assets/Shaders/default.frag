#version 430 core

#define LIGHT_MAX 256

struct Material{
	sampler2D diffuse;
	sampler2D specular;
	float Shininess;
};

struct PointLight{
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
	vec3 Position;

	float Constant;
	float Linear;
	float Quadratic;
};

struct DirectionalLight{
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
	vec3 Direction;
};

struct SpotLight{
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;

	vec3 Position;
	vec3 Direction;

	float Constant;
	float Linear;
	float Quadratic;
	float cutOff;
	float outerCutOff;
};

in vec2 TexCoord;
in vec4 ourColor;
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 CameraPos;
uniform sampler2D ourTexture;
uniform Material material;

uniform PointLight point_light[LIGHT_MAX];
uniform DirectionalLight directional_light;
uniform SpotLight spot_light[LIGHT_MAX];
uniform int PointLightCount;
uniform int SpotLightCount;

vec4 CalculateLighting(vec3 texDiffuse, vec3 texSpec, vec3 norm, vec3 viewDir);

void main()
{
    vec3 texDiffuse = vec3(texture(material.diffuse, TexCoord));
	vec3 texSpec = vec3(texture(material.specular, TexCoord));
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(CameraPos - FragPos);

    FragColor =  CalculateLighting(texDiffuse,texSpec,norm,viewDir) * ourColor;
}

vec4 CalculateLighting(vec3 texDiffuse, vec3 texSpec, vec3 norm, vec3 viewDir){

  vec4 res;
   for(int i=0;i<SpotLightCount;i++){
		vec3 lightDir = normalize(spot_light[i].Position - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);  
	
		float t = dot(lightDir,normalize(-spot_light[i].Direction));
		float epsilon = spot_light[i].cutOff - spot_light[i].outerCutOff;
		float intensity = clamp((t - spot_light[i].outerCutOff)/epsilon,0.0,1.0);

		float dist = distance(spot_light[i].Position,FragPos);
 		float attenuation = 1.0/(spot_light[i].Constant + (spot_light[i].Linear * dist) + (spot_light[i].Quadratic * dist * dist));
		float diff = max(dot(norm,lightDir),0.0);
		 
		float spec = pow(max(0,dot(viewDir, reflectDir)), material.Shininess);
		 
		vec3 ambient  = spot_light[i].Ambient  * texDiffuse * attenuation;
		vec3 diffuse  = spot_light[i].Diffuse  * diff * texDiffuse * attenuation * intensity;
		vec3 specular = spot_light[i].Specular * spec * texSpec * attenuation * intensity;
		 
		res+= vec4((ambient + diffuse + specular),1.0);
		}

		for(int i=0;i<PointLightCount;i++){
			vec3 lightDir = normalize(point_light[i].Position - FragPos);
			vec3 reflectDir = reflect(-lightDir, norm);  

			float diff = max(dot(norm,lightDir),0.0);
			float spec = pow(max(0,dot(viewDir, reflectDir)), material.Shininess);
			float dist = distance(point_light[i].Position,FragPos);
			float attenuation = 1.0/(point_light[i].Constant + (point_light[i].Linear * dist) + (point_light[i].Quadratic * dist * dist));
	
			vec3 ambient  = point_light[i].Ambient  * texDiffuse * attenuation;
			vec3 diffuse  = point_light[i].Diffuse  * diff * texDiffuse * attenuation;
			vec3 specular = point_light[i].Specular * spec * texSpec * attenuation;

			res+= vec4((ambient + diffuse + specular),1.0);
		 }

		vec3 lightDir = normalize(-directional_light.Direction);
		float diff = max(dot(norm,lightDir),0.0);
		vec3 reflectDir = reflect(-lightDir, norm);  
		float spec = pow(max(0,dot(viewDir, reflectDir)), material.Shininess);
	

		vec3 ambient  = directional_light.Ambient  * texDiffuse;
		vec3 diffuse  = directional_light.Diffuse  * diff * texDiffuse;
		vec3 specular = directional_light.Specular * spec * texSpec;

		res += vec4(ambient + diffuse+specular,0.0);

		return res;
}
