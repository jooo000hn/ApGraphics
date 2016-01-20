#include "vec3.h"
#include <math.h>
#include "mathUtils.h"
#include "Quaternion.h"

namespace apanoo {
	Vec3::Vec3()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vec3::Vec3(const float& x, const float& y, const float &z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vec3& Vec3::add(const Vec3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	Vec3& Vec3::subtract(const Vec3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}
	Vec3& Vec3::mutiply(const Vec3& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;

		return *this;
	}

	Vec3& Vec3::mutiply(const float& other)
	{
		x *= other;
		y *= other;
		z *= other;

		return *this;
	}

	Vec3& Vec3::divide(const Vec3& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;

		return *this;
	}

	Vec3& Vec3::divide(const float& other)
	{
		x /= other;
		y /= other;
		z /= other;

		return *this;
	}

	Vec3& Vec3::normalize()
	{
		auto length = sqrt(x * x + y * y + z * z);
		x /= length;
		y /= length;
		z /= length;

		return *this;
	}

	// 难点：旋转
	Vec3& Vec3::rotate(float angle, Vec3 axis)
	{
		float sinHalfAngle = (float)sin(toRadians(angle / 2));
		float cosHalfAngle = (float)cos(toRadians(angle / 2));

		float rX = axis.x * sinHalfAngle;
		float rY = axis.y * sinHalfAngle;
		float rZ = axis.z * sinHalfAngle;
		float rW = cosHalfAngle;

		// 四元数实现球面旋转
		Quaternion rotation = Quaternion(rX, rY, rZ, rW);
		Quaternion conjugate = rotation.conjugate();
		Quaternion w = rotation * (*this) * conjugate;

		x = w.x;
		y = w.y;
		z = w.z;

		return *this;
 	}

	Vec3 Vec3::cross(const Vec3& other)
	{
		float _x = y * other.z - z * other.y;
		float _y = z * other.x - x * other.z;
		float _z = x * other.y - y * other.x;

		return Vec3(_x, _y, _z);
	}

	// 操作符
	Vec3 operator+(Vec3 left, const Vec3& right)
	{
		Vec3 tmp = left;
		return tmp.add(right);
		// return left.add(right);
	}

	Vec3 operator-(Vec3 left, const Vec3& right)
	{
		Vec3 tmp = left;
		return tmp.subtract(right);
		// return left.subtract(right);
	}

	Vec3 operator*(Vec3 left, const Vec3& right)
	{
		Vec3 tmp = left;
		return tmp.mutiply(right);
		// return left.mutiply(right);
	}

	Vec3 operator*(Vec3 left, const float& right)
	{
		Vec3 tmp = left;
		return tmp.mutiply(right);
		// return left.mutiply(right);
	}

	Vec3 operator/(Vec3 left, const Vec3& right)
	{
		Vec3 tmp = left;
		return tmp.divide(right);
		// return left.divide(right);
	}

	Vec3 operator/(Vec3 left, const float& right)
	{
		Vec3 tmp = left;
		return tmp.divide(right);
		// return left.mutiply(right);
	}

	bool Vec3::operator==(const Vec3& other)
	{
		return x == other.x && y == other.y && z == other.z;
	}

	bool Vec3::operator!=(const Vec3& other)
	{
		return !(*this == other);
	}

	Vec3& Vec3::operator+=(const Vec3& other)
	{
		return add(other);
	}

	Vec3& Vec3::operator-=(const Vec3& other)
	{
		return subtract(other);
	}

	Vec3& Vec3::operator*=(const Vec3& other)
	{
		return mutiply(other);
	}

	Vec3& Vec3::operator/=(const Vec3& other)
	{
		return divide(other);
	}

	std::ostream& operator<<(std::ostream& stream, const Vec3& vector)
	{
		stream << "vec3:(" << vector.x << "," << vector.y << "," << vector.z << ")";
		return stream;
	}
}