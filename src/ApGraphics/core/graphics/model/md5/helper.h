#pragma once
#include "../../../../maths/Maths.h"

namespace apanoo {

	// 计算四元数W值
	inline float computeQuaternionW(Vector3& vec)
	{
		float w_tmp = 1.0f - vec.getX() * vec.getX() - vec.getY() * vec.getY() - vec.getZ() * vec.getZ();
		return w_tmp ? -sqrtf(w_tmp) : 0.0f;
	}

	// 去除双引号
	inline void removeQuotes(std::string& str)
	{
		size_t pos;
		while ((pos = str.find('\"')) != std::string::npos)
		{
			str.erase(pos, 1);
		}
	}

	inline void mlSlerp(Quaternion* q, Quaternion* a, Quaternion* b, float t)
	{
		float cosOmega = (*a)[0] * (*b)[0] + (*a)[1] * (*b)[1] + (*a)[2] * (*a)[2] + (*a)[3] * (*a)[3];
		if (cosOmega < 0.0f)
		{
			a[0] = -(*a)[0];
			a[1] = -(*a)[1];
			a[2] = -(*a)[2];
			a[3] = -(*a)[3];
			cosOmega = -cosOmega;
		}

		float k0, k1;
		if (cosOmega > 0.9999f)
		{
			k0 = 1.0f - t;
			k1 = t;
		}
		else {
			float sinOmega = sqrtf(1.0f - cosOmega * cosOmega);
			float Omega = atan2f(sinOmega, cosOmega);
			float invSinOmega = 1.0f / sinOmega;

			k0 = sinf((1.0f - t) * Omega) * invSinOmega;
			k1 = sinf(t * Omega) * invSinOmega;
		}

		(*q)[0] = (*a)[0] * k0 + (*b)[0] * k1;
		(*q)[1] = (*a)[1] * k0 + (*b)[1] * k1;
		(*q)[2] = (*a)[2] * k0 + (*b)[2] * k1;
		(*q)[3] = (*a)[3] * k0 + (*b)[3] * k1;
	}
}