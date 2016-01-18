#include "Mesh.h"

namespace apanoo {
	Mesh::Mesh()
	{
		glGenBuffers(1, &m_Vbo);
		m_Count = 0;
	}

	Mesh::~Mesh()
	{
	}

	void Mesh::addVertices(Vertex* vertices, GLsizei count)
	{
		m_Count = count;
		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
		glBufferData(GL_ARRAY_BUFFER, m_Count * Vertex::VERTEX_SIZE * 4, vertices, GL_STATIC_DRAW);
	}

	void Mesh::draw()
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Vertex::VERTEX_SIZE * 4, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
		glDrawArrays(GL_TRIANGLES, 0, m_Count);

		glDisableVertexAttribArray(0);
	}
}