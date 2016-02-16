#version 330 core

layout (location = 0) in vec3 Position;  
layout (location = 1) in vec2 TexCoord;  
layout (location = 2) in vec3 VertexNormal;  
layout (location = 3) in ivec4 BoneIDs;
layout (location = 4) in vec4 Weights;

out vec2 TexCoord0;

const int MAX_BONES = 100;

uniform mat4 Transform = mat4(1.0);
uniform mat4 gBones[MAX_BONES];

void main()
{
	// 根据权重计算骨骼变化矩阵
	mat4 BoneTransform = gBones[BoneIDs[0]] * Weights[0];
	BoneTransform     += gBones[BoneIDs[1]] * Weights[1];
	BoneTransform     += gBones[BoneIDs[2]] * Weights[2];
	BoneTransform     += gBones[BoneIDs[3]] * Weights[3];
	
	vec4 PosL = BoneTransform * vec4(Position, 1.0);
	
	// 最终位置
	if(PosL != 0) {
		gl_Position = Transform * PosL;
	} else {
		gl_Position = Transform * vec4(Position, 1.0);
	}
	
	// 纹理坐标
	TexCoord0 = TexCoord;
}
