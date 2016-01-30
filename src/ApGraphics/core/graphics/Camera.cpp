#include "Camera.h"

namespace apanoo {

	apanoo::Vector3 Camera::yAxis = Vector3(0, 1, 0);
	Camera::Camera(Vector3& pos, Vector3& forward, Vector3& up)
		: m_Position(pos), m_Forward(forward), m_Up(up)
	{
		m_Up = m_Up.Normalized();
		m_Forward = m_Forward.Normalized();
		// m_Up.normalize();
		// m_Forward.normalize();
	}

	Camera::Camera()
		: m_Position(Vector3(0, 0, 0)), m_Forward(Vector3(0, 0, 1)), m_Up(Vector3(0, 1, 0))
	{

	}

	Camera::~Camera()
	{
	}

	void Camera::move(Vector3& dir, const float& amt)
	{
		m_Position += dir * amt;
	}

	void Camera::input()
	{

	}

	Vector3 Camera::getLeft()
	{
		Vector3 left = m_Forward.Cross(m_Up);
		return left.Normalized();
	}

	Vector3 Camera::getRight()
	{
		Vector3 right = m_Up.Cross(m_Forward);
		return right.Normalized();
	}

	void Camera::rotateX(float angle)
	{
		Vector3 Haxis = yAxis.Cross(m_Forward).Normalized();
		
		m_Forward = m_Forward.Rotate(angle, Haxis).Normalized();

		m_Up = m_Forward.Cross(Haxis).Normalized();
	}

	void Camera::rotateY(float angle)
	{
		Vector3 Haxis = yAxis.Cross(m_Forward).Normalized();

		m_Forward = m_Forward.Rotate(angle, yAxis).Normalized();

		m_Up = m_Forward.Cross(Haxis).Normalized();
	}
}