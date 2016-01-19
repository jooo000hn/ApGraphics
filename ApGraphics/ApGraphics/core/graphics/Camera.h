#pragma once
#include "../../maths/maths.h"

namespace apanoo {
	class Camera
	{
	public:
		Camera(Vec3& pos, Vec3& forward, Vec3& up);
		~Camera();

		const inline Vec3& getPosition() const { return m_Position; }
		const inline Vec3& getForward() const { return m_Forward; }
		const inline Vec3& getUp() const { return m_Up; }

		void setPosition(Vec3& position) { m_Position = position; }
		void setForward(Vec3& forward) { m_Forward = forward; }
		void setUp(Vec3& up) { m_Up = up; }
	private:
		Vec3 m_Position;
		Vec3 m_Forward;
		Vec3 m_Up;
	};
}
