#pragma once
#include <vector>
#include "../Vertex.h"
#include "../Mesh.h"

namespace apanoo {
	class OBJ : public Mesh
	{
	public:
		OBJ(const char* filename);
		~OBJ();

	private:
		void loadOBJ(const char* filename);
	};
}
