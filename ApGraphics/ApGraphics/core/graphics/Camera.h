#pragma once
#include "../../maths/maths.h"

namespace apanoo {
	class Camera
	{
	public:
		Camera();
		Camera(Vec3& pos, Vec3& forward, Vec3& up);
		~Camera();

		// camera“∆∂Ø
		void move(Vec3& dir, const float& amt);

		void input();

		Vec3 getLeft();
		Vec3 getRight();

		void rotateX(float angle);
		void rotateY(float angle);

		inline Vec3& getPosition() { return m_Position; }
		inline Vec3& getForward() { return m_Forward; }
		inline Vec3& getUp() { return m_Up; }

		void setPosition(Vec3& position) { m_Position = position; }
		void setForward(Vec3& forward) { m_Forward = forward; }
		void setUp(Vec3& up) { m_Up = up; }
	private:
		Vec3 m_Position;
		Vec3 m_Forward;
		Vec3 m_Up;

	private:
		static Vec3 yAxis;
	};
}
