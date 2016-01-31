#version 330 core

layout (location = 0) in vec3 position;  
layout (location = 1) in vec2 texCoord;  
layout (location = 2) in vec3 VertexNormal;  

out vec3 LightIntensity;
out vec2 TexCoord0;

uniform vec4 LightPosition; // Light position in eye coords.
uniform vec3 Kd;            // Diffuse reflectivity
uniform vec3 Ld;            // Diffuse light intensity

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 transform = mat4(1.0);


void main()
{
	vec3 tnorm = normalize(NormalMatrix * VertexNormal);
	vec4 eyeCoords = ModelViewMatrix * vec4(position, 1.0);
	vec3 s = normalize(vec3(LightPosition - eyeCoords));
	LightIntensity = Ld * Kd * max(dot(s,tnorm),0.0);
	gl_Position = transform * vec4( position, 1.0);
	TexCoord0 = texCoord;
}
