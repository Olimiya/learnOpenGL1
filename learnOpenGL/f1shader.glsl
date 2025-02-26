﻿#version 460 core
out vec4 FragColor;

in vec2 texCoord;

// texture samplers
//uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragColor = texture(texture2, texCoord);
}