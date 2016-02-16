#version 330 core

in vec2 TexCoord0;
out vec4 outputColor;

uniform sampler2D Tex1;

void main(void)
{
	vec4 textureColor = texture(Tex1, TexCoord0);

	if(TexCoord0 != 0) {
		outputColor = textureColor;
	}
	else {
		outputColor = vec4(1, 0, 0, 1);
	}
}
