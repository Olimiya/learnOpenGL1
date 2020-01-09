#version 460 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
	mat3 TBN;
} fs_in;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;

uniform vec3 cameraPos;
uniform vec3 lightPos;

//uniform bool hasAmbient;
//uniform bool hasSpecular;
//uniform bool hasDiffuse;

void main()
{
	//凹凸贴图计算法向量
	vec3 normal = vec3(texture(normalMap, fs_in.TexCoords));
	normal = normalize(normal * 2 - 1);
	normal = normalize(fs_in.TBN * normal);

	//光照Phong计算
	//1.环境光
	vec3 ambient = vec3(texture(diffuseMap, fs_in.TexCoords)) * 0.1;

	//2.漫反射光
	vec3 lightDir = normalize(fs_in.FragPos - lightPos);
	float diff = max(dot(normal, -lightDir), 0.0);
	vec3 diffuse = (diff * vec3(texture(diffuseMap, fs_in.TexCoords)));

	//3.镜面反射光
	vec3 viewDir = normalize(fs_in.FragPos - cameraPos);
	//vec3 lightReflectDir = normalize(reflect(lightDir, norm));
	vec3 halfDir = normalize(-lightDir - viewDir);
	float spec = pow(max(dot(halfDir, normal), 0.0), 32);
	vec3 specular = spec * vec3(0.2);

	FragColor = vec4(diffuse, 1.0);
}
