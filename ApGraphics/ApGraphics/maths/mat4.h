/*
*  author : 谭锦志
*  email  : apanoo@126.com
*  time   : 2015 12 09
*/
#ifndef __MAT4_H__
#define __MAT4_H__

#include "vec3.h"
#include "vec4.h"
#include "mathUtils.h"

namespace apanoo {
	struct Mat4
	{
		union  // 4 * 16 字节 == 4 * 4 * 4 字节则：elements每四个元素相当于矩阵的一列
		{
			float elements[4 * 4];
			Vec4 columns[4];
		};

		Mat4();
		Mat4(float diagonal);

		// getColum
		Vec4 getCloum(int index)
		{
			index *= 4;
			return Vec4(elements[index + 1], elements[index + 2], elements[index + 3], elements[index + 4]);
		}

		// 逆矩阵
		Mat4& invert();

		// 单位矩阵
		static Mat4 identity();

		// 正交矩阵
		static Mat4 orthographic(float left, float right, float bottom, float top, float near, float far);

		// 透视矩阵
		static Mat4 perspective(float fov, float aspectRatio, float near, float far);

		// 平移矩阵
		static Mat4 translation(const Vec3& translation);

		// 旋转矩阵
		static Mat4 rotation(float angle, const Vec3& axis);

		// 放缩矩阵
		static Mat4 scale(const Vec3& scale);

		// 相乘
		Mat4& multiply(const Mat4& other);
		Vec3 multiply(const Vec3& vec) const;
		Vec4 multiply(const Vec4& vec) const;
		// 操作符
		friend Mat4 operator*(Mat4 left, const Mat4& right);
		friend Vec3 operator*(const Mat4& left, const Vec3& right);
		friend Vec4 operator*(const Mat4& left, const Vec4& right);
		Mat4 operator*=(const Mat4& other);
	};
}
#endif // !__MAT4_H__
