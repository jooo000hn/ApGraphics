/*
*  author : ̷��־
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

		// �����������������ֵ
		Vec3 cross(const Vec3& other);

		// ����������ı�����ֵ
		Vec3& add(const Vec3& other);
		Vec3& subtract(const Vec3& other);
		Vec3& mutiply(const Vec3& other);
		Vec3& mutiply(const float& other);
		Vec3& divide(const Vec3& other);
		Vec3& divide(const float& other);
		Vec3& normalize();
		Vec3& rotate(float angle, Vec3 axis); // ��ת

		// ������
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