#version 460 core
layout (location = 0) in vec3 vPostion;
layout (location = 1) in vec2 vtexCoords;
out vec2 texCoords;

void main()
{
	gl_Position = vec4(vPostion.x, vPostion.y, 0.0, 1.0);
	texCoords = vtexCoords;
}