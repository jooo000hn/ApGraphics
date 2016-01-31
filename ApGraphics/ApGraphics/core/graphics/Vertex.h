#pragma once
#include "../../maths/maths.h"
#include "gl/glew.h"

#define VERTEX_SIZE 5
namespace apanoo {
	struct Vertex
	{
	public:
		float x, y, z;  // 坐标点
		float s, t;     // 纹理坐标
		Vertex(float _x, float _y, float _z)   // 不带纹理
			: x(_x), y(_y), z(_z), s(0), t(0)
		{}
		Vertex(float _x, float _y, float _z, float _s, float _t)  // 带纹理
			: x(_x), y(_y), z(_z), s(_s), t(_t)
		{}
	};
}