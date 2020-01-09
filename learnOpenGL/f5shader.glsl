#version 460 core
//加载
struct Material
{
	sampler2D texture_ambient;

	sampler2D texture_diffuse;
	sampler2D texture_specular;
	//sampler2D emissionMap;
	//sampler2D normalMap;

	float shininess;
	vec3 ka;//环境光
	vec3 kd;//漫反射光
	vec3 ks;//镜面反射光
};

out vec4 FragColor;

in vec3 fragPosition;
in vec3 normal;
in vec2 texCoords;

uniform vec3 cameraPos;
//uniform sampler2D texture1;
uniform samplerCube skybox;
uniform Material material;

uniform bool hasAmbient;
uniform bool hasSpecular;
uniform bool hasDiffuse;

void main()
{
	//反射贴图
	vec3 viewDir = normalize(fragPosition - cameraPos);
	vec3 norm = normalize(normal);
	vec3 viewReflectDir = normalize(reflect(viewDir, norm));
	vec3 reflection;
	if(hasAmbient)
	{
		vec3 reflectMap = vec3(texture(material.texture_ambient, texCoords).rgb);
		reflection = vec3(texture(skybox, viewReflectDir).rgb) * reflectMap;
	}
	else  
		reflection = vec3(0,0,0);

	//光照Phong计算
	vec3 light = vec3(1.0,1.0,1.0);
	vec3 lightDir = vec3(0.0, 0.0, -1.0);
	//1.环境光
	vec3 ambient = vec3(texture(material.texture_diffuse, texCoords)) * 0.1 * light;

	//2.漫反射光
	float diff = max(dot(norm, -lightDir), 0.0);
	vec3 diffuse;
	if(hasDiffuse)
		diffuse = (diff * vec3(texture(material.texture_diffuse, texCoords))) * light;
	else 
		diffuse = (diff) * material.kd * light;

	//3.镜面反射光
	vec3 lightReflectDir = normalize(reflect(lightDir, norm));
	float spec = pow(max(dot(lightReflectDir, -viewDir), 0.0), material.shininess);
	vec3 specular;
	if(hasSpecular)
		specular = (spec * vec3(texture(material.texture_specular, texCoords))) * light;
	else  
		specular = (spec * material.ks) * light;

	FragColor = vec4(diffuse, 1.0);
}