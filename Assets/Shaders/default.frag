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
	DirectionalLight directional_light;
	Light lights [256]; 
};

in vec2 TexCoord;
in vec4 ourColor;
in vec3 FragPos;
in vec3 Normal;
in vec4 FragLightPos;

uniform vec3 CameraPos;
uniform Material material;
uniform sampler2D ShadowMap;
out vec4 FragColor;

float ShadowCalculation(vec4 fragPosLightSpace){
   vec3 projCoords = (fragPosLightSpace.xyz / fragPosLightSpace.w)* 0.5 + 0.5;
   float bias = 0.005;
   float closestDepth = texture(ShadowMap, projCoords.xy).r; 
   float currentDepth = projCoords.z;
   float shadow = currentDepth-bias < closestDepth  ? 1.0 : 0.0;
   return shadow;
}

vec3 CalcPointLight(vec3 texDiffuse, vec3 texSpec, vec3 norm, vec3 viewDir){
	int point_light_count = int(light_count.x);
	  vec3 res = vec3(0);
	  
	for(int i=0;i<point_light_count;i++){

		vec3 lightDir = normalize(lights[i].Position - FragPos);
		  
		vec3 halfwayDir = normalize(lightDir + viewDir);
		float diff = max(dot(norm,lightDir),0.0);
		float spec = pow(max(0,dot(viewDir, halfwayDir)), material.Shininess);
		float dist = distance(lights[i].Position,FragPos);
		float attenuation = 1.0/(lights[i].Attenuation.x + (lights[i].Attenuation.y * dist) + (lights[i].Attenuation.z * dist * dist));
	
		vec3 ambient  = lights[i].Ambient  * texDiffuse;
		vec3 diffuse  = lights[i].Diffuse  * diff * texDiffuse;
		vec3 specular = lights[i].Specular * spec * texSpec;

		res+= lights[i].Color*(ambient + diffuse + specular)* attenuation;
		}
		return res;
}

vec3 CalcSpotLight(vec3 texDiffuse, vec3 texSpec, vec3 norm, vec3 viewDir){

      int point_light_count = int(light_count.x);
      int spot_light_count = int(light_count.y);
	  vec3 res = vec3(0);

	  for(int i=point_light_count;i<point_light_count+spot_light_count;i++){
		vec3 lightDir = normalize(lights[i].Position - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);  
	
		float t = dot(lightDir,normalize(-lights[i].Direction));
		float epsilon = cos(radians(lights[i].cutOff.x)) - lights[i].cutOff.y;
		float intensity = clamp((t - cos(radians(lights[i].cutOff.y)))/epsilon,0.0,1.0);

		float dist = distance(lights[i].Position,FragPos);
 		float attenuation = 1.0/(lights[i].Attenuation.x + (lights[i].Attenuation.y * dist) + (lights[i].Attenuation.z * dist * dist));
		float diff = max(dot(norm,lightDir),0.0);
		 
		float spec = pow(max(0,dot(viewDir, reflectDir)), material.Shininess);
		 
		vec3 ambient  = lights[i].Ambient  * texDiffuse ;
		vec3 diffuse  = lights[i].Diffuse  * diff * texDiffuse * intensity;
		vec3 specular = lights[i].Specular * spec * texSpec * intensity;
		 
		res+=  lights[i].Color*(ambient + diffuse + specular)* attenuation;
		}
		return res;
}

vec3 CalculateDirectionalLight(vec3 texDiffuse, vec3 texSpec, vec3 norm, vec3 viewDir){
   float shadow =  ShadowCalculation(FragLightPos);   
   vec3 lightDir = normalize(-directional_light.Direction);
   float diff = max(dot(norm,lightDir),0.0);
   vec3 reflectDir = reflect(-lightDir, norm);  
   float spec = pow(max(0,dot(viewDir, reflectDir)), material.Shininess);
   
   
   vec3 ambient  = directional_light.Ambient  * texDiffuse;
   vec3 diffuse  = directional_light.Diffuse  * diff * texDiffuse;
   vec3 specular = directional_light.Specular * spec * texSpec;
  
   if(shadow == 0) ambient *= 0.1;

   return  directional_light.Color*(ambient + (diffuse + specular)*shadow);
}

vec4 CalculateLighting(vec3 texDiffuse, vec3 texSpec, vec3 norm, vec3 viewDir){
   
  
   vec3 pt_light = CalcPointLight(texDiffuse,texSpec,norm,viewDir);
   vec3 spt_light = CalcSpotLight(texDiffuse,texSpec,norm,viewDir);
   vec3 dir_light = CalculateDirectionalLight(texDiffuse,texSpec,norm,viewDir);

   return vec4(dir_light+pt_light+spt_light,1.0);
}



void main()
{
	    vec3 texDiffuse = vec3(texture(material.diffuse, TexCoord));
		vec3 texSpec = vec3(texture(material.specular, TexCoord));
		vec3 norm = normalize(Normal);
		vec3 viewDir = normalize(CameraPos - FragPos);
    

		vec4 light = CalculateLighting(texDiffuse,texSpec,norm,viewDir);
		
		float gamma = 2.2;
		FragColor = light  * ourColor;
		FragColor.rgb = pow(FragColor.rgb,vec3(1.0/gamma));
		
}