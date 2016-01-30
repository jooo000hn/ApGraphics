#include "Transform.h"

namespace apanoo {

	Transform::Transform()
		: m_Translation(Vector3(0, 0, 0)), m_Rotation(Vector3(0, 0, 0)), m_Scale(Vector3(1, 1, 1))
	{
	}

	Transform::~Transform()
	{

	}

	// ͸��ͶӰ,��ģ�ͱ任��������任(MVP)
	apanoo::Matrix4 Transform::getProjectionTransformation()
	{ 
		// �ۼƵ�ģ�ͱ任(M)
		Matrix4 transform = getTransformation(); 

		// ͶӰ����(P)
		Matrix4 projection = Matrix4().PerspectiveMatrix(m_Fov, (float)m_Width / (float)m_Height, m_Near, m_Far);

		// ���������(V)
		Matrix4 cameraRotation = Matrix4().CameraMatrix(m_Camera.getForward(), m_Camera.getUp());
		Matrix4 cameraTranslation = Matrix4().TranslationMatrix(Vector3(-m_Camera.getPosition().GetX(), -m_Camera.getPosition().GetY(), -m_Camera.getPosition().GetZ()));
		
		return projection * (cameraRotation * (cameraTranslation * transform));
	}

	// ģ�ͱ任(M)
	Matrix4 Transform::getTransformation()
	{
		Matrix4 translation = Matrix4().TranslationMatrix(m_Translation);
		Matrix4 rotation = Matrix4().RotationEulerMatrix(m_Rotation.GetX(), m_Rotation.GetY(), m_Rotation.GetZ());
		Matrix4 scale = Matrix4().ScaleMatrix(m_Scale);
		
		return translation * (rotation * scale);
	}
}