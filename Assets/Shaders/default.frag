#version 430 core

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

uniform vec3 CameraPos;
uniform sampler2D ourTexture;

uniform PointLight point_light;
uniform DirectionalLight directional_light;
uniform SpotLight spot_light;

uniform Material material;

out vec4 FragColor;

vec4 SpotLightFnc(SpotLight light){
   
	vec3 texDiffuse = vec3(texture(material.diffuse, TexCoord));
	vec3 texSpec = vec3(texture(material.specular, TexCoord));
	vec3 norm = normalize(Normal);
	
	vec3 lightDir = normalize(light.Position - FragPos);
    vec3 viewDir = normalize(CameraPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);  
	
	float t = dot(lightDir,normalize(-light.Direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((t - light.outerCutOff)/epsilon,0.0,1.0);

	float dist = distance(light.Position,FragPos);
 	float attenuation = 1.0/(light.Constant + (light.Linear * dist) + (light.Quadratic * dist * dist));
	float diff = max(dot(norm,lightDir),0.0);
		 
	float spec = pow(max(0,dot(viewDir, reflectDir)), material.Shininess);
		 
	vec3 ambient  = light.Ambient  * texDiffuse * attenuation;
	vec3 diffuse  = light.Diffuse  * diff * texDiffuse * attenuation * intensity;
	vec3 specular = light.Specular * spec * texSpec * attenuation * intensity;
		 
	return vec4((ambient + diffuse + specular),1.0);
	
}

vec4 DirectionLightFnc(DirectionalLight light){
	vec3 texDiffuse = vec3(texture(material.diffuse, TexCoord));
	vec3 texSpec = vec3(texture(material.specular, TexCoord));

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(-light.Direction);
	float diff = max(dot(norm,lightDir),0.0);

	vec3 viewDir = normalize(CameraPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(0,dot(viewDir, reflectDir)), material.Shininess);
	

	vec3 ambient  = light.Ambient  * texDiffuse;
	vec3 diffuse  = light.Diffuse  * diff * texDiffuse;
	vec3 specular = light.Specular * spec * texSpec;

	return  vec4(ambient + diffuse+specular,0.0);
}

vec4 PointLightFnc(PointLight light){
	vec3 texDiffuse = vec3(texture(material.diffuse, TexCoord));
	vec3 texSpec = vec3(texture(material.specular, TexCoord));

	float dist = distance(light.Position,FragPos);
	float attenuation = 1.0/(light.Constant + (light.Linear * dist) + (light.Quadratic * dist * dist));

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.Position - FragPos);
	float diff = max(dot(norm,lightDir),0.0);

	vec3 viewDir = normalize(CameraPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(0,dot(viewDir, reflectDir)), material.Shininess);
	
	vec3 ambient  = light.Ambient  * texDiffuse * attenuation;
	vec3 diffuse  = light.Diffuse  * diff * texDiffuse * attenuation;
	vec3 specular = light.Specular * spec * texSpec * attenuation;

	return vec4((ambient + diffuse + specular),1.0);
}

void main()
{

    FragColor =  SpotLightFnc(spot_light) * ourColor;
}