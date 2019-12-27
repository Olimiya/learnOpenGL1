#version 460 core
layout (location = 0) in vec3 vPostion;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;

out vec2 texCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
	gl_Position = projection * view * model * vec4(vPostion.xyz, 1.0);
	texCoord = vTexCoord;
	Normal = mat3(transpose(inverse(model))) * vNormal;
	FragPos = vec3(model * vec4(vPostion, 1.0));
}