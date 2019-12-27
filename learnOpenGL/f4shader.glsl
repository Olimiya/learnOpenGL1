#version 460 core
in vec2 texCoords;
out vec4 FragColor;

uniform sampler2D texture1;
void main()
{
    FragColor = texture(texture1, texCoords);
    if(FragColor.a < 0.05)
        discard;
	//FragColor = vec4(vec3(gl_FragCoord.z), 1.0);
}