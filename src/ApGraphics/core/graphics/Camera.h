#pragma once
#include "../../maths/maths.h"

namespace apanoo {

	class Window;
	class Camera
	{
	public:
		Camera();
		Camera(Vector3& pos, Vector3& forward, Vector3& up);
		~Camera();

		// camera移动
		void move(Vector3& dir, const float& amt);

		void update(Window* window, float RotationSensitivity, float MoveSensitivity);

		Vector3 getLeft();
		Vector3 getRight();

		void rotateX(float angle);
		void rotateY(float angle);

		inline Vector3& getPosition() { return m_Position; }
		inline Vector3& getForward() { return m_Forward; }
		inline Vector3& getUp() { return m_Up; }

		inline void setPosition(Vector3& position) { m_Position = position; }
		inline void setForward(Vector3& forward) { m_Forward = forward; }
		inline void setUp(Vector3& up) { m_Up = up; }
	private:
		Vector3 m_Position;  // 位置
		Vector3 m_Forward;   // 正前方
		Vector3 m_Up;        // 正上方

	private:
		static Vector3 yAxis;
	};
}
