/*
*  author : Ì·½õÖ¾
*  email  : apanoo@126.com
*  time   : 2015 12 09
*/

#ifndef __VEC2_H__
#define __VEC2_H__

#include <iostream>

struct Vec2f
{
	float x, y;
	Vec2f();
	Vec2f(const float &x, const float &y);

	Vec2f& add(const Vec2f& other); 
	Vec2f& subtract(const Vec2f& other);
	Vec2f& mutiply(const Vec2f& other);
	Vec2f& divide(const Vec2f& other);

	// ²Ù×÷·û
	friend Vec2f operator+(Vec2f left, const Vec2f& right);
	friend Vec2f operator-(Vec2f left, const Vec2f& right);
	friend Vec2f operator*(Vec2f left, const Vec2f& right);
	friend Vec2f operator/(Vec2f left, const Vec2f& right);

	bool operator==(const Vec2f& other);
	bool operator!=(const Vec2f& other);

	Vec2f& operator+=(const Vec2f& other);
	Vec2f& operator-=(const Vec2f& other);
	Vec2f& operator*=(const Vec2f& other);
	Vec2f& operator/=(const Vec2f& other);

	friend std::ostream& operator<<(std::ostream& stream, const Vec2f& vector);
};

#endif // !__VEC2_H__