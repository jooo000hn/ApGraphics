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

		// 顶点数组
		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
		glBufferData(GL_ARRAY_BUFFER, vcount * VERTEX_SIZE * sizeof(GL_FLOAT), vertices, GL_STATIC_DRAW);

		// 索引数组
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, icount * sizeof(GL_FLOAT), indices, GL_STATIC_DRAW);

	}

	void Mesh::draw()
	{
		// 启用shader中location=0的属性
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);

		// 指向shader中location=0的属性
		// 3是每个顶点中需要更新的元素个数
		// GL_FLOAT时数据类型
		// GL_FALSE表示传递数据前不归一化
		// 连续2元素之间的偏移字节数,这里是每个元素的大小： Vertex::VERTEX_SIZE * sizeof(GL_FLOAT)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(GL_FLOAT), 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);
		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
	}
}