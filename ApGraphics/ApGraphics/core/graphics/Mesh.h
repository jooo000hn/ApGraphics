#pragma once

#include "Vertex.h"
namespace apanoo {
	class Mesh
	{
	public:
		Mesh();
		~Mesh();
		void addVertices(Vertex* vertices, GLsizei count);
		void draw();
	private:
		GLuint m_Vbo;
		GLsizei m_Count;
	};
}