#pragma once
#include "../../maths/maths.h"
#include "gl/glew.h"

namespace apanoo {
	struct Vertex
	{
	public:
		static int VERTEX_SIZE;
		float x, y, z;
		Vertex(float x, float y, float z);
	};
}