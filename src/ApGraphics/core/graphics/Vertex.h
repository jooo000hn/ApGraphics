#pragma once
#include "../../maths/maths.h"
#include "gl/glew.h"

#define VERTEX_SIZE 8     // �����С
namespace apanoo {
	struct Vertex
	{
	public:
		Vector3 m_Pos;      // λ��
		Vector2 m_TexCoord; // ��������
		Vector3 m_Normal;   // ����
		Vertex(float _x, float _y, float _z)
		{
			m_Pos.setX(_x);
			m_Pos.setY(_y);
			m_Pos.setZ(_z);
		}
		Vertex(float _x, float _y, float _z, float _s, float _t)
		{
			m_Pos.setX(_x);
			m_Pos.setY(_y);
			m_Pos.setZ(_z);
			m_TexCoord.setX(_s);
			m_TexCoord.setY(_t);
		}
		Vertex(Vector3& pos, Vector2& tex, Vector3& normal)
			: m_Pos(pos), m_TexCoord(tex), m_Normal(normal)
		{

		}
	};
}