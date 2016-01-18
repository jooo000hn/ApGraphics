#include "Vertex.h"

namespace apanoo {
	int Vertex::VERTEX_SIZE = 3;
	Vertex::Vertex(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
}