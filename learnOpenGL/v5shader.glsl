#version 460 core
layout (location = 0) in vec3 vPostion;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;

out vec3 fragPosition;
out vec3 normal;
out vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
	normal = mat3(transpose(inverse(model))) * vNormal;
	fragPosition = vec3(model * vec4(vPostion, 1.0));
	gl_Position = projection * view * model * vec4(vPostion.xyz, 1.0);
	texCoords = vTexCoord;
}