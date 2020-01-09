#version 460 core
layout (location = 0) in vec3 vPostion;

out vec3 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
	vec4 pos = projection * view * vec4(vPostion.xyz, 1.0);
	gl_Position = pos.xyww;
	texCoord = vPostion;
}