#version 330 core
#define MAX_BONES 33

layout (location = 0) in vec3 Position;  // 位置
layout (location = 1) in vec2 TexCoord;  // 纹理坐标
layout (location = 2) in vec4 Indices;   // 索引
layout (location = 3) in vec4 Weights;   // 权重

out vec2 TexCoord0;

uniform mat4 Skinned[MAX_BONES];
uniform mat4 World;
uniform mat4 View;
uniform mat4 Proj;

void main()
{
	vec4 position = vec4(Position, 1.0f);
	vec4 result = Skinned[int(Indices.x)] * position * Weights.x;
	result = Skinned[int(Indices.y)] * position * Weights.y + result;
	result = Skinned[int(Indices.z)] * position * Weights.z + result;
	result = Skinned[int(Indices.w)] * position * Weights.w + result;
	
	gl_Position = World * result;
	gl_Position = View * gl_Position;
	gl_Position = Proj * gl_Position;
	
	// 纹理坐标
	TexCoord0 = TexCoord;
}
