#version 330 core
//in vec3 myColor;
in vec2 myTxtrCrd;

out vec4 color;

uniform float mixLevel;
uniform float opacityLevel;
uniform sampler2D myTexture1;
uniform sampler2D myTexture2;

void main()
{
	color = mix(texture(myTexture1, myTxtrCrd), texture(myTexture2, myTxtrCrd), mixLevel)/** mix(vec4(1.0f, 1.0f, 1.0f, 1.0f), vec4(myColor, 1.0f), opacityLevel)*/;
}