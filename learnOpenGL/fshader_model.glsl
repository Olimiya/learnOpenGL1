#version 460 core
//加载
struct Material
{
	//sampler2D ambient;
	sampler2D texture_diffuse;
	sampler2D texture_specular;
	//sampler2D emissionMap;
	//sampler2D normalMap;

	float shininess;

	vec3 ka;//环境光
	vec3 kd;//漫反射光
	vec3 ks;//镜面反射光
};
//光源都是自定义
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

//改变需要用的光源
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
	//这里需要统一选择一种恰当的光源组合方法
	//如：只有一个点光源
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
	vec3 ambient = vec3(texture(material.texture_diffuse, texCoord)) * light.ambient * material.ka;

	//2.漫反射光
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * vec3(texture(material.texture_diffuse, texCoord))) * light.diffuse * material.kd;

	//3.镜面反射光
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);
	vec3 specular = (spec * vec3(texture(material.texture_specular, texCoord))) * light.specular * material.ks;
	return ambient + diffuse + specular;
}
vec3 calPointLight(PointLight light, vec3 norm, vec3 FragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.pos - FragPos);
	//1.环境光
	vec3 ambient = vec3(texture(material.texture_diffuse, texCoord)) * light.ambient * material.ka;

	//2.漫反射光
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * vec3(texture(material.texture_diffuse, texCoord)))
	* light.diffuse * material.kd;

	//3.镜面反射光
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);
	vec3 specular = (spec * vec3(texture(material.texture_specular, texCoord)))
	* light.specular * material.ks;

	float dist = length(FragPos - light.pos);
	float attenuation = 1.0f / (1.0f + light.linear * dist + light.quadratic * dist * dist);
	return (ambient + diffuse + specular) * attenuation;
}
vec3 calSpotLight(SpotLight light, vec3 norm, vec3 FragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.pos - FragPos);

	//1.环境光
	vec3 ambient = vec3(texture(material.texture_diffuse, texCoord)) * light.ambient * material.ka;

	//2.漫反射光
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * vec3(texture(material.texture_diffuse, texCoord))) * light.diffuse * material.kd;

	//3.镜面反射光
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);
	vec3 specular = (spec * vec3(texture(material.texture_specular, texCoord))) * light.specular * material.ks;

	float theta     = dot(lightDir, normalize(-light.direction));
	float epsilon   = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);  

	float dist = length(FragPos - light.pos);
	float attenuation = 1.0f / (1.0f + light.linear * dist + light.quadratic * dist * dist);
	return (ambient + diffuse + specular) * attenuation * intensity;
}