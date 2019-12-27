#version 460 core
layout (location = 0) in vec3 vPostion;
layout (location = 1) in vec2 vtexCoords;
out vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(vPostion.xyz, 1.0);
	texCoords = vtexCoords;
}