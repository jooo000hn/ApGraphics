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
		Matrix4 projection = Matrix4().perspectiveMatrix(m_Fov, (float)m_Width / (float)m_Height, m_Near, m_Far);

		// ���������(V)
		Matrix4 cameraRotation = Matrix4().cameraMatrix(m_Camera.getForward(), m_Camera.getUp());
		Matrix4 cameraTranslation = Matrix4().translationMatrix(Vector3(-m_Camera.getPosition().getX(), -m_Camera.getPosition().getY(), -m_Camera.getPosition().getZ()));
		
		return projection * (cameraRotation * (cameraTranslation * transform));
	}

	// ģ�ͱ任(M)
	Matrix4 Transform::getTransformation()
	{
		Matrix4 translation = Matrix4().translationMatrix(m_Translation);
		Matrix4 rotation = Matrix4().rotationEulerMatrix(m_Rotation.getX(), m_Rotation.getY(), m_Rotation.getZ());
		Matrix4 scale = Matrix4().scaleMatrix(m_Scale);
		
		return translation * (rotation * scale);
	}
}