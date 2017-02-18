#version 330 core
//in vec3 myColor;
in vec2 myTxtrCrd;

out vec4 color;

uniform sampler2D myTexture1;

void main()
{
	color = texture(myTexture1, myTxtrCrd);
}