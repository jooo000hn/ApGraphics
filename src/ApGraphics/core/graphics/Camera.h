#pragma once
#include "../../maths/maths.h"

namespace apanoo {
	class Camera
	{
	public:
		Camera();
		Camera(Vector3& pos, Vector3& forward, Vector3& up);
		~Camera();

		// camera“∆∂Ø
		void move(Vector3& dir, const float& amt);

		void input();

		Vector3 getLeft();
		Vector3 getRight();

		void rotateX(float angle);
		void rotateY(float angle);

		inline Vector3& getPosition() { return m_Position; }
		inline Vector3& getForward() { return m_Forward; }
		inline Vector3& getUp() { return m_Up; }

		void setPosition(Vector3& position) { m_Position = position; }
		void setForward(Vector3& forward) { m_Forward = forward; }
		void setUp(Vector3& up) { m_Up = up; }
	private:
		Vector3 m_Position;
		Vector3 m_Forward;
		Vector3 m_Up;

	private:
		static Vector3 yAxis;
	};
}
