#version 430 core

#define Constant x
#define Linear   y
#define Quadratic z


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
	vec3 Attenuation;
	vec3 Color;
	vec3 Direction;
	vec3 cutOff; 
};

struct PointLight{  
	vec3 Ambient;    
	vec3 Diffuse;    
	vec3 Specular;   
	vec3 Position;   
	vec3 Attenuation;
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

struct DirectionalLight{ 
	vec3 Ambient;     
	vec3 Diffuse;     
	vec3 Specular;    
	vec3 Direction;
	vec3 Color;
};
	
 
layout(std140, binding = 1) uniform Lights
{
	vec2 light_count;
	DirectionalLight directional_light; //i:16 s:64
	Light lights [256]; //i:64 s: 104 qnt: 128
};

in vec2 TexCoord;
in vec4 ourColor;
in vec3 FragPos;
in vec3 Normal;

uniform vec3 CameraPos;
uniform sampler2D ourTexture;
uniform Material material;

out vec4 FragColor;


vec4 CalculateLighting(vec3 texDiffuse, vec3 texSpec, vec3 norm, vec3 viewDir){

   int point_light_count = int(light_count.x);
   int spot_light_count = int(light_count.y);
   vec3 res = vec3(0);

   for(int i=0;i<point_light_count;i++){
		vec3 lightDir = normalize(lights[i].Position - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);  
	
		float t = dot(lightDir,normalize(-lights[i].Direction));
		float epsilon = lights[i].cutOff.x - lights[i].cutOff.y;
		float intensity = clamp((t - lights[i].cutOff.y)/epsilon,0.0,1.0);

		float dist = distance(lights[i].Position,FragPos);
 		float attenuation = 1.0/(lights[i].Attenuation.x + (lights[i].Attenuation.y * dist) + (lights[i].Attenuation.z * dist * dist));
		float diff = max(dot(norm,lightDir),0.0);
		 
		float spec = pow(max(0,dot(viewDir, reflectDir)), material.Shininess);
		 
		vec3 ambient  = lights[i].Ambient  * texDiffuse * attenuation;
		vec3 diffuse  = lights[i].Diffuse  * diff * texDiffuse * attenuation * intensity;
		vec3 specular = lights[i].Specular * spec * texSpec * attenuation * intensity;
		 
		res+=  lights[i].Color*(ambient + diffuse + specular);
		}

	for(int i=point_light_count;i<point_light_count+spot_light_count;i++){
		vec3 lightDir = normalize(lights[i].Position - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);  

		float diff = max(dot(norm,lightDir),0.0);
		float spec = pow(max(0,dot(viewDir, reflectDir)), material.Shininess);
		float dist = distance(lights[i].Position,FragPos);
		float attenuation = 1.0/(lights[i].Attenuation.x + (lights[i].Attenuation.y * dist) + (lights[i].Attenuation.z * dist * dist));
	
		vec3 ambient  = lights[i].Ambient  * texDiffuse * attenuation;
		vec3 diffuse  = lights[i].Diffuse  * diff * texDiffuse * attenuation;
		vec3 specular = lights[i].Specular * spec * texSpec * attenuation;

		res+= lights[i].Color*(ambient + diffuse + specular);
		}

		vec3 lightDir = normalize(-directional_light.Direction);
		float diff = max(dot(norm,lightDir),0.0);
		vec3 reflectDir = reflect(-lightDir, norm);  
		float spec = pow(max(0,dot(viewDir, reflectDir)), material.Shininess);
	

		vec3 ambient  = directional_light.Ambient  * texDiffuse;
		vec3 diffuse  = directional_light.Diffuse  * diff * texDiffuse;
		vec3 specular = directional_light.Specular * spec * texSpec;

		res += directional_light.Color*(ambient + diffuse + specular);

		return vec4(res,1.0);
}


void main()
{
	    vec3 texDiffuse = vec3(texture(material.diffuse, TexCoord));
		vec3 texSpec = vec3(texture(material.specular, TexCoord));
		vec3 norm = normalize(Normal);
		vec3 viewDir = normalize(CameraPos - FragPos);
        
		vec4 light = CalculateLighting(texDiffuse,texSpec,norm,viewDir);
		
		
			FragColor = light * texture(ourTexture, TexCoord) * ourColor;
		
		
}