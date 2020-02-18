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
	vec3 Attenuation;
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
	vec3 Direction;	  
	vec3 Position;    
	vec3 Attenuation; 
	vec2 cutOff;      
 
};
uniform	PointLight point_light [128];		
uniform	SpotLight spot_light   [128];		
 
layout(std140, binding = 1) uniform Lights
{
	vec2 light_count;
	DirectionalLight directional_light; //i:16 s:64

};

in vec2 TexCoord;
in vec4 ourColor;
in vec3 FragPos;
in vec3 Normal;

uniform vec3 CameraPos;
uniform sampler2D ourTexture;
uniform Material material;

out vec4 FragColor;



void main()
{
	    vec3 texDiffuse = vec3(texture(material.diffuse, TexCoord));
		vec3 texSpec = vec3(texture(material.specular, TexCoord));
		vec3 norm = normalize(Normal);
		vec3 viewDir = normalize(CameraPos - FragPos);
        vec3 lightDir = normalize(-directional_light.Direction);
		float diff = max(dot(norm,lightDir),0.0);
		vec3 reflectDir = reflect(-lightDir, norm);  
		float spec = pow(max(0,dot(viewDir, reflectDir)), material.Shininess);
	

		vec3 ambient  = directional_light.Ambient  * texDiffuse;
		vec3 diffuse  = directional_light.Diffuse  * diff * texDiffuse;
		vec3 specular = directional_light.Specular * spec * texSpec;

		
		FragColor = vec4(ambient + diffuse+specular,0.0) + texture(ourTexture, TexCoord) * ourColor;
	
}