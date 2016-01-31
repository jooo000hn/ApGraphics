#version 330 core

layout (location=0) out vec4 fColor;

in vec2 texCoord0;
in vec4 ColorNoTexture;

uniform sampler2D sampler;

void main()
{
	if(texCoord0 == 0)
		fColor = ColorNoTexture;
	else
		fColor = texture(sampler, texCoord0.xy);
}