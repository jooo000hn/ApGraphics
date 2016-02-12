#include "Camera.h"
#include "../window/Window.h"

namespace apanoo {

	apanoo::Vector3 Camera::yAxis = Vector3(0, 1, 0);
	Camera::Camera(Vector3& pos, Vector3& forward, Vector3& up)
		: m_Position(pos), m_Forward(forward), m_Up(up)
	{
		this->setUp(m_Up.normalized());
		this->setForward(m_Forward.normalized());
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

	void Camera::update(Window* window, float RotationSensitivity, float MoveSensitivity)
	{
		// 鼠标旋转镜头
		const Vector2 center = window->getCenter();
		Vector2 cursor = window->getCursorPosition();
		Vector2 delta = cursor - center;

		bool rotY = delta.getX() != 0;
		bool rotX = delta.getY() != 0;

		if (rotY)
		{
			rotateY(delta.getX() * RotationSensitivity);
		}
		if (rotX)
		{
			rotateX(delta.getY() * RotationSensitivity);
		}

		if (rotX || rotY)
		{
			window->setCursorPosition(center.getX(), center.getY());
		}

		// 按键控制移动
		if (window->isKeyPressed(GLFW_KEY_W))
		{
			move(getForward(), MoveSensitivity);
		}
		if (window->isKeyPressed(GLFW_KEY_S))
		{
			move(getForward(), -MoveSensitivity);
		}
		if (window->isKeyPressed(GLFW_KEY_A))
		{
			move(getLeft(), MoveSensitivity);
		}
		if (window->isKeyPressed(GLFW_KEY_D))
		{
			move(getRight(), MoveSensitivity);
		}
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
		
		this->setForward(m_Forward.rotate(angle, Haxis).normalized());
		this->setUp(m_Forward.cross(Haxis).normalized());
	}

	void Camera::rotateY(float angle)
	{
		Vector3 Haxis = yAxis.cross(m_Forward).normalized();

		this->setForward(m_Forward.rotate(angle, yAxis).normalized());
		this->setUp(m_Forward.cross(Haxis).normalized());
	}
}