#pragma once

#include "Vertex.h"
namespace apanoo {
	class Mesh
	{
	public:
		Mesh();
		~Mesh();
		void addVertices(Vertex* vertices, GLsizei vcount, int* indices, GLsizei icount);
		void render();
	private:
		GLuint m_Vbo; // vertex buffer object
		GLuint m_Ibo; // index buffe object
		GLsizei m_IndexCount;
	};
}