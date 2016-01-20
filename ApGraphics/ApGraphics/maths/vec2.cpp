#include "vec2.h"

namespace apanoo {
	Vec2::Vec2()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vec2::Vec2(const float& x, const float& y)
	{
		this->x = x;
		this->y = y;
	}

	Vec2& Vec2::add(const Vec2& other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}

	Vec2& Vec2::subtract(const Vec2& other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}

	Vec2& Vec2::mutiply(const Vec2& other)
	{
		x *= other.x;
		y *= other.y;

		return *this;
	}

	Vec2& Vec2::mutiply(const float& other)
	{
		x *= other;
		y *= other;

		return *this;
	}

	Vec2& Vec2::divide(const Vec2& other)
	{
		x /= other.x;
		y /= other.y;

		return *this;
	}

	Vec2& Vec2::divide(const float& other)
	{
		x /= other;
		y /= other;

		return *this;
	}

	// ²Ù×÷·û
	Vec2 operator+(Vec2 left, const Vec2& right)
	{
		Vec2 tmp = left;
		return tmp.add(right);
	}

	Vec2 operator-(Vec2 left, const Vec2& right)
	{
		Vec2 tmp = left;
		return tmp.subtract(right);
	}

	Vec2 operator*(Vec2 left, const Vec2& right)
	{
		Vec2 tmp = left;
		return tmp.mutiply(right);
	}

	Vec2 operator*(const float& left, Vec2& right)
	{
		Vec2 tmp = right;
		return tmp.mutiply(left);
	}

	Vec2 operator*(Vec2 left, const float& right)
	{
		Vec2 tmp = left;
		return tmp.mutiply(right);
	}


	Vec2 operator/(Vec2 left, const Vec2& right)
	{
		Vec2 tmp = left;
		return tmp.divide(right);
	}

	Vec2 operator/(Vec2 left, const float& right)
	{
		Vec2 tmp = left;
		return tmp.divide(right);
	}

	bool Vec2::operator==(const Vec2& other)
	{
		return x == other.x && y == other.y;
	}

	bool Vec2::operator!=(const Vec2& other)
	{
		return !(*this == other);
	}

	Vec2& Vec2::operator+=(const Vec2& other)
	{
		return add(other);
	}

	Vec2& Vec2::operator-=(const Vec2& other)
	{
		return subtract(other);
	}

	Vec2& Vec2::operator*=(const Vec2& other)
	{
		return mutiply(other);
	}

	Vec2& Vec2::operator/=(const Vec2& other)
	{
		return divide(other);
	}

	std::ostream& operator<<(std::ostream& stream, const Vec2& vector)
	{
		stream << "vec2:(" << vector.x << "," << vector.y << ")";
		return stream;
	}
}