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
		glBufferData(GL_ARRAY_BUFFER, vcount * sizeof(Vertex), vertices, GL_STATIC_DRAW);

		// 索引数组
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, icount * sizeof(GL_UNSIGNED_INT), indices, GL_STATIC_DRAW);

	}

	void Mesh::render()
	{
		// location = 0
		glEnableVertexAttribArray(0);
		// location = 1
		glEnableVertexAttribArray(1);

		// 纹理
		glEnableVertexAttribArray(1);


		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);

		// 指向shader中location=0的属性
		// 3是每个顶点中需要更新的元素个数
		// GL_FLOAT时数据类型
		// GL_FALSE表示传递数据前不归一化
		// 连续2元素之间的偏移字节数,这里是每个元素的大小： Vertex::VERTEX_SIZE * sizeof(GL_FLOAT)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(GL_FLOAT), 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(GL_FLOAT), (const GLvoid*)(3 * sizeof(GLfloat)));

		// 纹理坐标
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(GL_FLOAT), (void *)12);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);
		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0);

		// location = 0
		glDisableVertexAttribArray(0);
<<<<<<< HEAD:src/ApGraphics/core/graphics/model/Mesh.cpp
		// location = 1
=======
>>>>>>> origin/master:ApGraphics/ApGraphics/core/graphics/Mesh.cpp
		glDisableVertexAttribArray(1);
	}
}