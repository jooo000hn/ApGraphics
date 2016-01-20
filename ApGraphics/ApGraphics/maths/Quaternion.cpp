#include "Quaternion.h"

namespace apanoo {

	Quaternion::Quaternion(const float &x, const float &y, const float &z, const float &w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	float Quaternion::length()
	{
		return sqrt(x * x + y * y + z * z + w * w);
	}

	Quaternion& Quaternion::normalize()
	{
		float _length = this->length();
		this->x /= _length;
		this->y /= _length;
		this->z /= _length;
		this->w /= _length;
		return *this;
	}

	Quaternion& Quaternion::conjugate()
	{
		Quaternion tmp(-this->x, -this->y, -this->z, this->w);
		return tmp;
	}

	Quaternion& Quaternion::mutiply(const Quaternion& other)
	{
		float _w = w * other.w - x * other.x - y * other.y - z * other.z;
		float _x = x * other.w + w * other.x + y * other.z - z * other.y;
		float _y = y * other.w + w * other.y + z * other.x - x * other.z;
		float _z = z * other.w + w * other.z + x * other.y - y * other.x;

		this->x = _x;
		this->y = _y;
		this->z = _z;
		this->w = _w;

		return *this;
	}

	Quaternion& Quaternion::mutiply(const Vec3& vec)
	{
		float _w = -x * vec.x - y * vec.y - z * vec.z;
		float _x =  w * vec.x + y * vec.z - z * vec.y;
		float _y =  w * vec.y + z * vec.x - x * vec.z;
		float _z =  w * vec.z + x * vec.y - y * vec.x;

		this->x = _x;
		this->y = _y;
		this->z = _z;
		this->w = _w;

		return *this;
	}

	Quaternion operator *(Quaternion left, const Quaternion& right)
	{
		Quaternion tmp = left;
		return tmp.mutiply(right);
	}

	Quaternion operator *(Quaternion left, const Vec3& vec)
	{
		Quaternion tmp = left;
		return tmp.mutiply(vec);
	}

}