#include "vec4.h"

namespace apanoo {
	Vec4::Vec4(const float& x, const float& y, const float &z, const float &w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Vec4& Vec4::add(const Vec4& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;

		return *this;
	}

	Vec4& Vec4::subtract(const Vec4& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;

		return *this;
	}
	Vec4& Vec4::mutiply(const Vec4& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;

		return *this;
	}
	Vec4& Vec4::divide(const Vec4& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;

		return *this;
	}

	// ²Ù×÷·û
	Vec4 operator+(Vec4 left, const Vec4& right)
	{
		return left.add(right);
	}

	Vec4 operator-(Vec4 left, const Vec4& right)
	{
		return left.subtract(right);
	}

	Vec4 operator*(Vec4 left, const Vec4& right)
	{
		return left.mutiply(right);
	}

	Vec4 operator/(Vec4 left, const Vec4& right)
	{
		return left.divide(right);
	}

	bool Vec4::operator==(const Vec4& other)
	{
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}

	bool Vec4::operator!=(const Vec4& other)
	{
		return !(*this == other);
	}

	Vec4& Vec4::operator+=(const Vec4& other)
	{
		return add(other);
	}

	Vec4& Vec4::operator-=(const Vec4& other)
	{
		return subtract(other);
	}

	Vec4& Vec4::operator*=(const Vec4& other)
	{
		return mutiply(other);
	}

	Vec4& Vec4::operator/=(const Vec4& other)
	{
		return divide(other);
	}


	std::ostream& operator<<(std::ostream& stream, const Vec4& vector)
	{
		stream << "vec4:(" << vector.x << "," << vector.y << "," << vector.z << "," << vector.w << ")";
		return stream;
	}
}