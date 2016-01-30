// �ṩ͸��ͶӰ�Լ�����ƽ�ơ���ת�������ȱ任
#pragma once
#include "../../maths/maths.h"
#include "Camera.h"

namespace apanoo {
	class Transform
	{
	public:
		Transform();
		~Transform();

		// ��ͼ�任 TODO : ��װ setProjection Ϊ��̬
		Matrix4 getProjectionTransformation();
		void setProjection(float fov, float width, float height, float near, float far)
		{
			m_Fov    = fov;
			m_Width  = width;
			m_Height = height;
			m_Near   = near;
			m_Far    = far;
		}

		// ����� TODO : ��װ setCamera Ϊ��̬
		void setCamera(Camera camera){ m_Camera = camera; }
		inline Camera* getCamera() { return &m_Camera; }

		// ����ģ�ͱ任
		Matrix4 getTransformation();

		// ƽ�� x, y, zΪƽ����
		inline const Vector3 getTranslation() const { return m_Translation; }
		void setTranslation(Vector3& translation) { m_Translation = translation; }
		void setTranslation(float x, float y, float z) { m_Translation = Vector3(x, y, z); }

		// ��ת x, y, zΪ����ת����ת�ĽǶ�
		inline const Vector3 getRotation() const { return m_Rotation; }
		void setRotation(Vector3& rotation) { m_Rotation = rotation; }
		void setRotation(float x, float y, float z) { m_Rotation = Vector3(x, y, z); }

		// ���� x, y, zΪ��������
		inline const Vector3 getScale() const { return m_Scale; }
		void setScale(Vector3& scale) { m_Scale = scale; }
		void setScale(float x, float y, float z) { m_Scale = Vector3(x, y, z); }

	private:

		// ģ�ͱ任����
		Vector3 m_Translation;
		Vector3 m_Rotation;
		Vector3 m_Scale;

		// ͸��ͶӰ����
		float m_Near;
		float m_Far;
		float m_Width;
		float m_Height;
		float m_Fov;

		// �����
		Camera m_Camera;
	};
}
