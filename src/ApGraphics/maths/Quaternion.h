#pragma once
#ifndef _INC_MATH
	#include <math.h>
#endif // !_INC_MATH

#ifndef _IOSTREAM_
	#include <iostream>
#endif // !_IOSTREAM_

#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"

namespace apanoo {
	class Quaternion : public Vector4
	{
	public:
		Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f)
		{
			(*this)[0] = x;
			(*this)[1] = y;
			(*this)[2] = z;
			(*this)[3] = w;
		}

		// ��ά�����ʼ����Ԫ��
		Quaternion(const Vector4& r);

		// ʹ����ת�����ת�Ƕȳ�ʼ����Ԫ��
		Quaternion(const Vector3& axis, float angle);

		// ʹ�þ����ʼ����Ԫ�� �� ����ת��Ԫ��
		Quaternion(const Matrix4& m);

		// ���Բ�ֵ
		Quaternion NLerp(const Quaternion& r, float lerpFactor, bool shortestPath) const;

		// �������Բ�ֵ
		Quaternion SLerp(const Quaternion& r, float lerpFactor, bool shortestPath) const;

		// ��Ԫ��ת��ά����
		Matrix4 ToRotationMatrix() const;

		// ����ǰ��������
		Vector3 GetForward() const;

		// ������������
		Vector3 GetBack() const;

		// �����Ϸ�������
		Vector3 GetUp() const;

		// �����·�������
		Vector3 GetDown() const;

		// �����ҷ�������
		Vector3 GetRight() const;

		// ������������
		Vector3 GetLeft() const;

		// ����
		Quaternion Conjugate() const;

		Quaternion operator*(const Quaternion& r) const;

		Quaternion operator*(const Vector3& v) const;

		friend std::ostream& operator<<(std::ostream& stream, const Quaternion& quaternion);
	};
}