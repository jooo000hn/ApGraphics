#pragma once
#include "../../maths/maths.h"
#include "gl/glew.h"

#define VERTEX_SIZE 3
namespace apanoo {
	struct Vertex
	{
	public:
		float x, y, z;
		Vertex(float _x, float _y, float _z)
			: x(_x), y(_y), z(_z)
		{}
	};
}