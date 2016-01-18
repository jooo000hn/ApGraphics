#version 330

layout (location=0) out vec4 fColor;
in vec4 color;

void main()
{
	fColor = color;
}