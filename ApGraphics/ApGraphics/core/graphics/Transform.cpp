#include "Transform.h"

namespace apanoo {
	Transform::Transform()
		: m_Translation(Vec3(0, 0, 0)), m_Rotation(Vec3(0, 0, 0)), m_Scale(Vec3(1, 1, 1))
	{
	}

	Transform::~Transform()
	{

	}

	// ͸��ͶӰ - ����ģ�ͱ任��������任
	apanoo::Mat4 Transform::getProjectionTransformation()
	{ 
		// �ۼƵ�ģ�ͱ任
		Mat4 transform = getTransformation(); 

		// ͶӰ����
		Mat4 projection = Mat4::projection(m_Fov, m_Width, m_Height, m_Near, m_Far);

		// ���������
		Mat4 cameraRotation = Mat4::camera(m_Camera.getForward(), m_Camera.getUp());
		Mat4 cameraTranslation = Mat4::translation(Vec3(-m_Camera.getPosition().x, -m_Camera.getPosition().y, -m_Camera.getPosition().z));
		
		return projection * (cameraRotation * (cameraTranslation * transform));
	}

	// ģ�ͱ任
	Mat4 Transform::getTransformation()
	{
		Mat4 translation = Mat4::translation(m_Translation);
		Mat4 rotation = Mat4::rotation(m_Rotation.x, m_Rotation.y, m_Rotation.z);
		Mat4 scale = Mat4::scale(m_Scale);

		return translation * (rotation * scale);
	}
}