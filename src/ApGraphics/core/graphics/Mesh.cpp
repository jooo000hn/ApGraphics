#include "Mesh.h"

namespace apanoo {
	Mesh::Mesh()
	{
		glGenBuffers(1, &m_Vbo);
		glGenBuffers(1, &m_Ibo);
		m_IndexCount = 0;
	}

	Mesh::~Mesh()
	{
	}

	void Mesh::addVertices(Vertex* vertices, GLsizei vcount, int* indices, GLsizei icount)
	{
		m_IndexCount = icount;

		// ��������
		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
		glBufferData(GL_ARRAY_BUFFER, vcount * VERTEX_SIZE * sizeof(GL_FLOAT), vertices, GL_STATIC_DRAW);

		// ��������
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, icount * sizeof(GL_FLOAT), indices, GL_STATIC_DRAW);

	}

	void Mesh::draw()
	{
		// ����shader��location=0������
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);

		// ָ��shader��location=0������
		// 3��ÿ����������Ҫ���µ�Ԫ�ظ���
		// GL_FLOATʱ��������
		// GL_FALSE��ʾ��������ǰ����һ��
		// ����2Ԫ��֮���ƫ���ֽ���,������ÿ��Ԫ�صĴ�С�� Vertex::VERTEX_SIZE * sizeof(GL_FLOAT)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(GL_FLOAT), 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);
		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
	}
}