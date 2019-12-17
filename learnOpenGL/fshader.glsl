﻿#version 460 core
out vec4 FragColor;

in vec2 texCoord;
//in vec3 color;

//uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	//FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.2);
	FragColor = texture(texture2, texCoord);
}