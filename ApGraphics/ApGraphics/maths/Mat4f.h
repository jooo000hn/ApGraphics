/*
*  author : ̷��־
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
	union  // 4 * 16 �ֽ� == 4 * 4 * 4 �ֽ���elementsÿ�ĸ�Ԫ���൱�ھ����һ��
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

	// �����
	Mat4f& invert();

	// ��λ����
	static Mat4f identity();

	// ��������
	static Mat4f orthographic(float left, float right, float bottom, float top, float near, float far);

	// ͸�Ӿ���
	static Mat4f perspective(float fov, float aspectRatio, float near, float far);

	// ƽ�ƾ���
	static Mat4f translation(const Vec3f& translation);

	// ��ת����
	static Mat4f rotation(float angle, const Vec3f& axis);

	// ��������
	static Mat4f scale(const Vec3f& scale);

	// ���
	Mat4f& multiply(const Mat4f& other);
	Vec3f multiply(const Vec3f& vec) const;
	Vec4f multiply(const Vec4f& vec) const; 
	// ������
	friend Mat4f operator*(Mat4f left, const Mat4f& right);
	friend Vec3f operator*(const Mat4f& left, const Vec3f& right);
	friend Vec4f operator*(const Mat4f& left, const Vec4f& right);
	Mat4f operator*=(const Mat4f& other);
}; 

#endif // !__MAT4_H__
