#include "Camera.h"

namespace apanoo {

	apanoo::Vec3 Camera::yAxis = Vec3(0, 1, 0);
	Camera::Camera(Vec3& pos, Vec3& forward, Vec3& up)
		: m_Position(pos), m_Forward(forward), m_Up(up)
	{
		m_Up.normalize();
		m_Forward.normalize();
	}

	Camera::Camera()
		: m_Position(Vec3(0, 0, 0)), m_Forward(Vec3(0, 0, 1)), m_Up(Vec3(0, 1, 0))
	{

	}

	Camera::~Camera()
	{
	}

	void Camera::move(Vec3& dir, const float& amt)
	{
		m_Position += dir * amt;
	}

	void Camera::input()
	{

	}

	Vec3 Camera::getLeft()
	{
		Vec3 left = m_Forward.cross(m_Up);
		return left.normalize();
	}

	Vec3 Camera::getRight()
	{
		Vec3 right = m_Up.cross(m_Forward);
		return right.normalize();
	}

	void Camera::rotateX(float angle)
	{
		Vec3 Haxis = yAxis.cross(m_Forward).normalize();
		
		m_Forward.rotate(angle, Haxis).normalize();

		m_Up = m_Forward.cross(Haxis).normalize();
	}

	void Camera::rotateY(float angle)
	{
		Vec3 Haxis = yAxis.cross(m_Forward).normalize();

		m_Forward.rotate(angle, yAxis).normalize();

		m_Up = m_Forward.cross(Haxis).normalize();
	}
}