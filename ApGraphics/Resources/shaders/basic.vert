#version 330

layout(location = 0) in vec3 position;

uniform mat4 pr_matrix = mat4(1.0);

out vec4 color;

void main()
{
	color = vec4(clamp(position, 0.0, 1.0), 1.0);
	gl_Position = pr_matrix * vec4(position, 1.0);
}