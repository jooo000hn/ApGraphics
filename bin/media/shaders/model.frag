#version 330 core

in vec3 LightIntensity;
in vec2 TexCoord0;
out vec4 outputColor;

uniform sampler2D Tex1;

void main(void)
{
	vec4 textureColor = texture(Tex1, TexCoord0);
	vec4 lightColor = vec4(LightIntensity, 1.0);
	
	//outputColor = mix(textureColor, lightColor, 0.1);
	if(TexCoord0 != 0) {
		outputColor = textureColor;
	}
	else {
		outputColor = vec4(1, 0, 0, 1);
	}
}
