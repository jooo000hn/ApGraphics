/*
*  author : 谭锦志
*  email  : apanoo@126.com
*  time   : 2015 12 09
*/
#ifndef __MAT4_H__
#define __MAT4_H__

#include "Vec3f.h"
#include "Vec4f.h"
#include "mathUtils.h"

struct Mat4f
{
	union  // 4 * 16 字节 == 4 * 4 * 4 字节则：elements每四个元素相当于矩阵的一列
	{
		float elements[4 * 4];
		Vec4f columns[4];
	};

	Mat4f();
	Mat4f(float diagonal);

	// getColum
	Vec4f getCloum(int index)
	{
		index *= 4;
		return Vec4f(elements[index + 1], elements[index + 2], elements[index + 3], elements[index + 4]);
	}

	// 逆矩阵
	Mat4f& invert();

	// 单位矩阵
	static Mat4f identity();

	// 正交矩阵
	static Mat4f orthographic(float left, float right, float bottom, float top, float near, float far);

	// 透视矩阵
	static Mat4f perspective(float fov, float aspectRatio, float near, float far);

	// 平移矩阵
	static Mat4f translation(const Vec3f& translation);

	// 旋转矩阵
	static Mat4f rotation(float angle, const Vec3f& axis);

	// 放缩矩阵
	static Mat4f scale(const Vec3f& scale);

	// 相乘
	Mat4f& multiply(const Mat4f& other);
	Vec3f multiply(const Vec3f& vec) const;
	Vec4f multiply(const Vec4f& vec) const; 
	// 操作符
	friend Mat4f operator*(Mat4f left, const Mat4f& right);
	friend Vec3f operator*(const Mat4f& left, const Vec3f& right);
	friend Vec4f operator*(const Mat4f& left, const Vec4f& right);
	Mat4f operator*=(const Mat4f& other);
}; 

#endif // !__MAT4_H__
