#version 460 core
in vec3 vPostion;
//in vec3 vColor;
in vec2 vTexCoord;

//out vec3 color;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
	gl_Position = projection * view * model * vec4(vPostion.xyz, 1.0);
	//color = vColor;
	texCoord = vTexCoord;
}