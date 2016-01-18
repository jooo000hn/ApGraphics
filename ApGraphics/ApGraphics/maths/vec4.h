/*
*  author : 谭锦志
*  email  : apanoo@126.com
*  time   : 2015 12 09
*/

#ifndef __VEC4_H__
#define __VEC4_H__

#include <iostream>

namespace apanoo {
	struct Vec4
	{
		float x, y, z, w;

		Vec4() = default;  // ！！（mat4返回列）
		Vec4(const float &x, const float &y, const float &z, const float &w);

		Vec4& add(const Vec4& other);
		Vec4& subtract(const Vec4& other);
		Vec4& mutiply(const Vec4& other);
		Vec4& divide(const Vec4& other);

		// 操作符
		friend Vec4 operator+(Vec4 left, const Vec4& right);
		friend Vec4 operator-(Vec4 left, const Vec4& right);
		friend Vec4 operator*(Vec4 left, const Vec4& right);
		friend Vec4 operator/(Vec4 left, const Vec4& right);

		bool operator==(const Vec4& other);
		bool operator!=(const Vec4& other);

		Vec4& operator+=(const Vec4& other);
		Vec4& operator-=(const Vec4& other);
		Vec4& operator*=(const Vec4& other);
		Vec4& operator/=(const Vec4& other);

		friend std::ostream& operator<<(std::ostream& stream, const Vec4& vector);
	};
}
#endif // !__VEC4_H__