#version 460 core
struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	//sampler2D emissionMap;
	float shininess;
};
struct DirLight
{
    vec3  direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
struct PointLight
{
	vec3 pos;

	float constant;
    float linear;
    float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
struct SpotLight
{
	vec3 pos;
    vec3  direction;
    float cutOff;
	float outerCutOff;

	float constant;
    float linear;
    float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
#define NR_POINT_LIGHTS 4

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 texCoord;

uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;

uniform vec3 viewPos;
vec3 calDirLight(DirLight light, vec3 norm, vec3 viewDir);
vec3 calPointLight(PointLight light, vec3 norm, vec3 FragPos, vec3 viewDir);
vec3 calSpotLight(SpotLight light, vec3 norm, vec3 FragPos, vec3 viewDir);

void main()
{
	vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

	vec3 result = calDirLight(dirLight, norm, viewDir);
    // phase 2: point lights
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += calPointLight(pointLights[i], norm, FragPos, viewDir);    
    // phase 3: spot light
    result += calSpotLight(spotLight, norm, FragPos, viewDir);    
	FragColor = vec4(result, 1.0);
}

vec3 calDirLight(DirLight light, vec3 norm, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	//1.环境光
	vec3 ambient = vec3(texture(material.diffuse, texCoord)) * light.ambient;

	//2.漫反射光
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * vec3(texture(material.diffuse, texCoord))) * light.diffuse;

	//3.镜面反射光
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);
	vec3 specular = (spec * vec3(texture(material.specular, texCoord))) * light.specular;
	return ambient + diffuse + specular;
}
vec3 calPointLight(PointLight light, vec3 norm, vec3 FragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.pos - FragPos);
	//1.环境光
	vec3 ambient = vec3(texture(material.diffuse, texCoord)) * light.ambient;

	//2.漫反射光
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * vec3(texture(material.diffuse, texCoord))) * light.diffuse;

	//3.镜面反射光
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);
	vec3 specular = (spec * vec3(texture(material.specular, texCoord))) * light.specular;

	float dist = length(FragPos - light.pos);
	float attenuation = 1.0f / (1.0f + light.linear * dist + light.quadratic * dist * dist);
	return (ambient + diffuse + specular) * attenuation;
}
vec3 calSpotLight(SpotLight light, vec3 norm, vec3 FragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.pos - FragPos);

	//1.环境光
	vec3 ambient = vec3(texture(material.diffuse, texCoord)) * light.ambient;

	//2.漫反射光
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * vec3(texture(material.diffuse, texCoord))) * light.diffuse;

	//3.镜面反射光
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);
	vec3 specular = (spec * vec3(texture(material.specular, texCoord))) * light.specular;

	float theta     = dot(lightDir, normalize(-light.direction));
	float epsilon   = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);  

	float dist = length(FragPos - light.pos);
	float attenuation = 1.0f / (1.0f + light.linear * dist + light.quadratic * dist * dist);
	return (ambient + diffuse + specular) * attenuation * intensity;
}