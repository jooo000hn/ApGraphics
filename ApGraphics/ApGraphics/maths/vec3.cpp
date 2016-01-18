#include "vec3.h"

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
	Vec3& Vec3::divide(const Vec3& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;

		return *this;
	}

	// ²Ù×÷·û
	Vec3 operator+(Vec3 left, const Vec3& right)
	{
		return left.add(right);
	}

	Vec3 operator-(Vec3 left, const Vec3& right)
	{
		return left.subtract(right);
	}

	Vec3 operator*(Vec3 left, const Vec3& right)
	{
		return left.mutiply(right);
	}

	Vec3 operator/(Vec3 left, const Vec3& right)
	{
		return left.divide(right);
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