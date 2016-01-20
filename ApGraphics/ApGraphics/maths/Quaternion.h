#pragma once
#include "maths.h"

namespace apanoo {
	struct Quaternion
	{
		float x, y, z, w;
		Quaternion(const float &x, const float &y, const float &z, const float &w);

		// ����ı�
		Quaternion& normalize();
		Quaternion& mutiply(const Quaternion& other);
		Quaternion& mutiply(const Vec3& vec);

		// ������
		Quaternion& conjugate();
		float length();

		// ������ ������
		friend Quaternion operator*(Quaternion left, const Quaternion& right);
		friend Quaternion operator*(Quaternion left, const Vec3& vec);
	};
}