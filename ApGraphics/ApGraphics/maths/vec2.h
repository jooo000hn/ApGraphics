/*
*  author : Ì·½õÖ¾
*  email  : apanoo@126.com
*  time   : 2015 12 09
*/

#ifndef __VEC2_H__
#define __VEC2_H__

#include <iostream>

namespace apanoo {
	struct Vec2
	{
		float x, y;
		Vec2();
		Vec2(const float &x, const float &y);

		Vec2& add(const Vec2& other);
		Vec2& subtract(const Vec2& other);
		Vec2& mutiply(const Vec2& other);
		Vec2& mutiply(const float& other);
		Vec2& divide(const Vec2& other);
		Vec2& divide(const float& other);

		// ²Ù×÷·û
		friend Vec2 operator+(Vec2 left, const Vec2& right);
		friend Vec2 operator-(Vec2 left, const Vec2& right);
		friend Vec2 operator*(Vec2 left, const Vec2& right);
		friend Vec2 operator*(const float& left, Vec2& right);
		friend Vec2 operator*(Vec2 left, const float& right);
		friend Vec2 operator/(Vec2 left, const Vec2& right);
		friend Vec2 operator/(Vec2 left, const float& right);

		bool operator==(const Vec2& other);
		bool operator!=(const Vec2& other);

		Vec2& operator+=(const Vec2& other);
		Vec2& operator-=(const Vec2& other);
		Vec2& operator*=(const Vec2& other);
		Vec2& operator/=(const Vec2& other);

		friend std::ostream& operator<<(std::ostream& stream, const Vec2& vector);
	};
}
#endif // !__VEC2_H__