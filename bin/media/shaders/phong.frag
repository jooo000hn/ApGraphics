#version 330 core

layout (location=0) out vec4 fColor;

in vec2 texCoord0;

uniform vec3 baseColor = vec3(1, 1, 1);
uniform vec3 ambientLight;
uniform sampler2D sampler;

void main()
{
	vec4 totalLigth = vec4(ambientLight, 1);
	vec4 color = vec4(baseColor, 1);

	if(texCoord0 != 0) {
		color *= texture(sampler, texCoord0.xy);
	}

	fColor = color * totalLigth;
}