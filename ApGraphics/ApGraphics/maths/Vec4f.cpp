#include "Vec4f.h"

Vec4f::Vec4f(const float& x, const float& y, const float &z, const float &w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vec4f& Vec4f::add(const Vec4f& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;

	return *this;
}

Vec4f& Vec4f::subtract(const Vec4f& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;

	return *this;
}
Vec4f& Vec4f::mutiply(const Vec4f& other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	w *= other.w;

	return *this;
}
Vec4f& Vec4f::divide(const Vec4f& other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;
	w /= other.w;

	return *this;
}

// ²Ù×÷·û
Vec4f operator+(Vec4f left, const Vec4f& right)
{
	return left.add(right);
}

Vec4f operator-(Vec4f left, const Vec4f& right)
{
	return left.subtract(right);
}

Vec4f operator*(Vec4f left, const Vec4f& right)
{
	return left.mutiply(right);
}

Vec4f operator/(Vec4f left, const Vec4f& right)
{
	return left.divide(right);
}

bool Vec4f::operator==(const Vec4f& other)
{
	return x == other.x && y == other.y && z == other.z && w == other.w;
}

bool Vec4f::operator!=(const Vec4f& other)
{
	return !(*this == other);
}

Vec4f& Vec4f::operator+=(const Vec4f& other)
{
	return add(other);
}

Vec4f& Vec4f::operator-=(const Vec4f& other)
{
	return subtract(other);
}

Vec4f& Vec4f::operator*=(const Vec4f& other)
{
	return mutiply(other);
}

Vec4f& Vec4f::operator/=(const Vec4f& other)
{
	return divide(other);
}


std::ostream& operator<<(std::ostream& stream, const Vec4f& vector)
{
	stream << "vec4:(" << vector.x << "," << vector.y << "," << vector.z << "," << vector.w << ")";
	return stream;
}