#pragma once
#include "maths.h"

namespace apanoo {
	struct Quaternion
	{
		float x, y, z, w;
		Quaternion(const float &x, const float &y, const float &z, const float &w);

		// 自身改变
		Quaternion& normalize();
		Quaternion& mutiply(const Quaternion& other);
		Quaternion& mutiply(const Vec3& vec);

		// 自身不变
		Quaternion& conjugate();
		float length();

		// 操作符 自身不变
		friend Quaternion operator*(Quaternion left, const Quaternion& right);
		friend Quaternion operator*(Quaternion left, const Vec3& vec);
	};
}