#include "Transform.h"

namespace apanoo {

	Transform::Transform()
		: m_Translation(Vector3(0, 0, 0)), m_Rotation(Vector3(0, 0, 0)), m_Scale(Vector3(1, 1, 1))
	{
	}

	Transform::~Transform()
	{

	}

	// 透视投影 - 包含模型变换和摄像机变换
	apanoo::Matrix4 Transform::getProjectionTransformation()
	{ 
		// 累计的模型变换
		Matrix4 transform = getTransformation(); 

		// 投影矩阵
		Matrix4 projection = Matrix4().Perspective(m_Fov, (float)m_Width / (float)m_Height, m_Near, m_Far);

		// 摄像机矩阵
		//Matrix4 cameraRotation = Matrix4::camera(m_Camera.getForward(), m_Camera.getUp());
		//Matrix4 cameraTranslation = Matrix4().Translation(Vector3(-m_Camera.getPosition().GetX(), -m_Camera.getPosition().GetY(), -m_Camera.getPosition().GetZ()));
		
		//return projection * (cameraRotation * (cameraTranslation * transform));
		return projection * transform;
	}

	// 模型变换
	Matrix4 Transform::getTransformation()
	{
		Matrix4 translation = Matrix4().Translation(m_Translation);
		Matrix4 rotation = Matrix4().RotationEuler(m_Rotation.GetX(), m_Rotation.GetY(), m_Rotation.GetZ());
		Matrix4 scale = Matrix4().Scale(m_Scale);
		
		return translation * (rotation * scale);
	}
}