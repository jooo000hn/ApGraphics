/*
*  author : Ì·½õÖ¾
*  email  : apanoo@126.com
*  time   : 2015 12 09
*/

#ifndef __VEC3_H__
#define __VEC3_H__

#include <iostream>

struct Vec3f
{
	float x, y, z;
	Vec3f();
	Vec3f(const float &x, const float &y, const float &z);

	Vec3f& add(const Vec3f& other); 
	Vec3f& subtract(const Vec3f& other);
	Vec3f& mutiply(const Vec3f& other);
	Vec3f& divide(const Vec3f& other);

	// ²Ù×÷·û
	friend Vec3f operator+(Vec3f left, const Vec3f& right);
	friend Vec3f operator-(Vec3f left, const Vec3f& right);
	friend Vec3f operator*(Vec3f left, const Vec3f& right);
	friend Vec3f operator/(Vec3f left, const Vec3f& right);

	bool operator==(const Vec3f& other);
	bool operator!=(const Vec3f& other);

	Vec3f& operator+=(const Vec3f& other);
	Vec3f& operator-=(const Vec3f& other);
	Vec3f& operator*=(const Vec3f& other);
	Vec3f& operator/=(const Vec3f& other);

	friend std::ostream& operator<<(std::ostream& stream, const Vec3f& vector);
};

#endif // !__VEC3_H__