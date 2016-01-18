/*
*  author : ̷��־
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
		union  // 4 * 16 �ֽ� == 4 * 4 * 4 �ֽ���elementsÿ�ĸ�Ԫ���൱�ھ����һ��
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

		// �����
		Mat4& invert();

		// ��λ����
		static Mat4 identity();

		// ��������
		static Mat4 orthographic(float left, float right, float bottom, float top, float near, float far);

		// ͸�Ӿ���
		static Mat4 perspective(float fov, float aspectRatio, float near, float far);

		// ƽ�ƾ���
		static Mat4 translation(const Vec3& translation);

		// ��ת����
		static Mat4 rotation(float angle, const Vec3& axis);

		// ��������
		static Mat4 scale(const Vec3& scale);

		// ���
		Mat4& multiply(const Mat4& other);
		Vec3 multiply(const Vec3& vec) const;
		Vec4 multiply(const Vec4& vec) const;
		// ������
		friend Mat4 operator*(Mat4 left, const Mat4& right);
		friend Vec3 operator*(const Mat4& left, const Vec3& right);
		friend Vec4 operator*(const Mat4& left, const Vec4& right);
		Mat4 operator*=(const Mat4& other);
	};
}
#endif // !__MAT4_H__
