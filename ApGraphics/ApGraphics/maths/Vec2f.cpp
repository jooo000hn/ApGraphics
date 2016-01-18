#include "Vec2f.h"

Vec2f::Vec2f()
{
	x = 0.0f;
	y = 0.0f;
}

Vec2f::Vec2f(const float& x, const float& y)
{
	this->x = x;
	this->y = y;
}

Vec2f& Vec2f::add(const Vec2f& other)
{
	x += other.x;
	y += other.y;

	return *this;
}

Vec2f& Vec2f::subtract(const Vec2f& other)
{
	x -= other.x;
	y -= other.y;

	return *this;
}
Vec2f& Vec2f::mutiply(const Vec2f& other)
{
	x *= other.x;
	y *= other.y;

	return *this;
}
Vec2f& Vec2f::divide(const Vec2f& other)
{
	x /= other.x;
	y /= other.y;

	return *this;
}

// ²Ù×÷·û
Vec2f operator+(Vec2f left, const Vec2f& right)
{
	return left.add(right);
}

Vec2f operator-(Vec2f left, const Vec2f& right)
{
	return left.subtract(right);
}

Vec2f operator*(Vec2f left, const Vec2f& right)
{
	return left.mutiply(right);
}

Vec2f operator/(Vec2f left, const Vec2f& right)
{
	return left.divide(right);
}

bool Vec2f::operator==(const Vec2f& other)
{
	return x == other.x && y == other.y;
}

bool Vec2f::operator!=(const Vec2f& other)
{
	return !(*this == other);
}

Vec2f& Vec2f::operator+=(const Vec2f& other)
{
	return add(other);
}

Vec2f& Vec2f::operator-=(const Vec2f& other)
{
	return subtract(other);
}

Vec2f& Vec2f::operator*=(const Vec2f& other)
{
	return mutiply(other);
}

Vec2f& Vec2f::operator/=(const Vec2f& other)
{
	return divide(other);
}


std::ostream& operator<<(std::ostream& stream, const Vec2f& vector)
{
	stream << "vec2:(" << vector.x << "," << vector.y << ")";
	return stream;
}