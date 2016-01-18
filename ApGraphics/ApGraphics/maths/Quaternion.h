#pragma once
#include "maths.h"

namespace apanoo {
	struct Quaternion
	{
		float x, y, z, w;
		Quaternion();
		Quaternion(const float &x, const float &y, const float &z, const float &w);

		float length();
		Quaternion& normalize();
		Quaternion& conjugate();
		Quaternion& mutiply(const Quaternion& other);
		Quaternion& mutiply(const Vec3& vec);

		// ²Ù×÷·û
		friend Quaternion operator*(Quaternion left, const Quaternion& right);
		friend Quaternion operator*(Quaternion left, const Vec3& vec);
	};
}