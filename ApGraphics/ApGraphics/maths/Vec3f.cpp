#include "Vec3f.h"

Vec3f::Vec3f()
{
	x = 0.0f;
	y = 0.0f;
}

Vec3f::Vec3f(const float& x, const float& y, const float &z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vec3f& Vec3f::add(const Vec3f& other)
{
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}

Vec3f& Vec3f::subtract(const Vec3f& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}
Vec3f& Vec3f::mutiply(const Vec3f& other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;

	return *this;
}
Vec3f& Vec3f::divide(const Vec3f& other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;

	return *this;
}

// ²Ù×÷·û
Vec3f operator+(Vec3f left, const Vec3f& right)
{
	return left.add(right);
}

Vec3f operator-(Vec3f left, const Vec3f& right)
{
	return left.subtract(right);
}

Vec3f operator*(Vec3f left, const Vec3f& right)
{
	return left.mutiply(right);
}

Vec3f operator/(Vec3f left, const Vec3f& right)
{
	return left.divide(right);
}

bool Vec3f::operator==(const Vec3f& other)
{
	return x == other.x && y == other.y && z == other.z;
}

bool Vec3f::operator!=(const Vec3f& other)
{
	return !(*this == other);
}

Vec3f& Vec3f::operator+=(const Vec3f& other)
{
	return add(other);
}

Vec3f& Vec3f::operator-=(const Vec3f& other)
{
	return subtract(other);
}

Vec3f& Vec3f::operator*=(const Vec3f& other)
{
	return mutiply(other);
}

Vec3f& Vec3f::operator/=(const Vec3f& other)
{
	return divide(other);
}


std::ostream& operator<<(std::ostream& stream, const Vec3f& vector)
{
	stream << "vec3:(" << vector.x << "," << vector.y << "," << vector.z << ")";
	return stream;
}