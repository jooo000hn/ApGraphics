#include "Camera.h"

namespace apanoo {

	apanoo::Vector3 Camera::yAxis = Vector3(0, 1, 0);
	Camera::Camera(Vector3& pos, Vector3& forward, Vector3& up)
		: m_Position(pos), m_Forward(forward), m_Up(up)
	{
		m_Up = m_Up.normalized();
		m_Forward = m_Forward.normalized();
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
		Vector3 left = m_Forward.cross(m_Up);
		return left.normalized();
	}

	Vector3 Camera::getRight()
	{
		Vector3 right = m_Up.cross(m_Forward);
		return right.normalized();
	}

	void Camera::rotateX(float angle)
	{
		Vector3 Haxis = yAxis.cross(m_Forward).normalized();
		
		m_Forward = m_Forward.rotate(angle, Haxis).normalized();

		m_Up = m_Forward.cross(Haxis).normalized();
	}

	void Camera::rotateY(float angle)
	{
		Vector3 Haxis = yAxis.cross(m_Forward).normalized();

		m_Forward = m_Forward.rotate(angle, yAxis).normalized();

		m_Up = m_Forward.cross(Haxis).normalized();
	}
}