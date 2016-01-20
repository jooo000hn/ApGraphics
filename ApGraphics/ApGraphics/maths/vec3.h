/*
*  author : 谭锦志
*  email  : apanoo@126.com
*  time   : 2015 12 09
*/

#ifndef __VEC3_H__
#define __VEC3_H__

#include <iostream>

namespace apanoo {
	struct Vec3
	{
		float x, y, z;
		Vec3();
		Vec3(const float &x, const float &y, const float &z);

		// 操作：不会更改自身值
		Vec3 cross(const Vec3& other);

		// 操作：均会改变自身值
		Vec3& add(const Vec3& other);
		Vec3& subtract(const Vec3& other);
		Vec3& mutiply(const Vec3& other);
		Vec3& mutiply(const float& other);
		Vec3& divide(const Vec3& other);
		Vec3& divide(const float& other);
		Vec3& normalize();
		Vec3& rotate(float angle, Vec3 axis); // 旋转

		// 操作符
		friend Vec3 operator+(Vec3 left, const Vec3& right);
		friend Vec3 operator-(Vec3 left, const Vec3& right);
		friend Vec3 operator*(Vec3 left, const Vec3& right);
		friend Vec3 operator*(Vec3 left, const float& right);
		friend Vec3 operator/(Vec3 left, const Vec3& right);
		friend Vec3 operator/(Vec3 left, const float& right);

		bool operator==(const Vec3& other);
		bool operator!=(const Vec3& other);

		Vec3& operator+=(const Vec3& other);
		Vec3& operator-=(const Vec3& other);
		Vec3& operator*=(const Vec3& other);
		Vec3& operator/=(const Vec3& other);

		friend std::ostream& operator<<(std::ostream& stream, const Vec3& vector);
	};
}
#endif // !__VEC3_H__