/*
*  author : 谭锦志
*  email  : apanoo@126.com
*  time   : 2015 12 09
*/

#ifndef __VEC4_H__
#define __VEC4_H__

#include <iostream>

struct Vec4f
{
	float x, y, z, w;

	Vec4f() = default;  // ！！（mat4返回列）
	Vec4f(const float &x, const float &y, const float &z, const float &w);

	Vec4f& add(const Vec4f& other);
	Vec4f& subtract(const Vec4f& other);
	Vec4f& mutiply(const Vec4f& other);
	Vec4f& divide(const Vec4f& other);

	// 操作符
	friend Vec4f operator+(Vec4f left, const Vec4f& right);
	friend Vec4f operator-(Vec4f left, const Vec4f& right);
	friend Vec4f operator*(Vec4f left, const Vec4f& right);
	friend Vec4f operator/(Vec4f left, const Vec4f& right);

	bool operator==(const Vec4f& other);
	bool operator!=(const Vec4f& other);

	Vec4f& operator+=(const Vec4f& other);
	Vec4f& operator-=(const Vec4f& other);
	Vec4f& operator*=(const Vec4f& other);
	Vec4f& operator/=(const Vec4f& other);

	friend std::ostream& operator<<(std::ostream& stream, const Vec4f& vector);
};

#endif // !__VEC4_H__