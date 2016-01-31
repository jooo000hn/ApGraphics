#version 330

// Î»ÖÃ
layout(location = 0) in vec3 position;

// ÎÆÀí×ø±ê
layout(location = 1) in vec2 texCoord;

uniform mat4 transform = mat4(1.0);

out vec2 texCoord0;

void main()
{
	gl_Position = transform * vec4(position, 1.0) ;
	texCoord0 = texCoord;
}