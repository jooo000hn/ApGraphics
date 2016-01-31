#pragma once
#include <vector>
#include "../Vertex.h"
#include "Mesh.h"

namespace apanoo {
	// ֻ֧��3����
	class OBJMesh : public Mesh
	{
	public:
		OBJMesh(const char* filename);
		~OBJMesh();

	private:
		void loadOBJ(const char* filename);
	};
}
