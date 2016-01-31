#pragma once
#include "../../maths/maths.h"
#include "gl/glew.h"

#define VERTEX_SIZE 5
namespace apanoo {
	struct Vertex
	{
	public:
		float x, y, z;  // �����
		float s, t;     // ��������
		Vertex(float _x, float _y, float _z)   // ��������
			: x(_x), y(_y), z(_z), s(0), t(0)
		{}
		Vertex(float _x, float _y, float _z, float _s, float _t)  // ������
			: x(_x), y(_y), z(_z), s(_s), t(_t)
		{}
	};
}