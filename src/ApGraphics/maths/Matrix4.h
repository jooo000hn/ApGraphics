#pragma once
#ifndef _INC_MATH
	#include <math.h>
#endif // !_INC_MATH

#ifndef _IOSTREAM_
	#include <iostream>
#endif // !_IOSTREAM_

#include "Vector3.h"
#include "Vector4.h"

namespace apanoo {
	/*
	* ע�⣺m[i][j] j��ʾ�У�i��ʾ��
	* ʹ����������Ҫ��Shader��glUniformMatrix4fv������������
	* ʹ���͵�shader�ľ��󱣳ִ洢��ʽһ��
	*/
	class Matrix4
	{
	public:
		Matrix4() { }

		Matrix4(const Matrix4& r)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				for (unsigned int i = 0; i < 4; i++)
				{
					(*this)[i][j] = r[i][j];
				}
			}
		}

		Matrix4(float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33)
		{
			// ��һ��
			(*this)[0][0] = m00;
			(*this)[1][0] = m01;
			(*this)[2][0] = m02;
			(*this)[3][0] = m03;

			// �ڶ���
			(*this)[0][1] = m10;
			(*this)[1][1] = m11;
			(*this)[2][1] = m12;
			(*this)[3][1] = m13;

			// ������
			(*this)[0][2] = m20;
			(*this)[1][2] = m21;
			(*this)[2][2] = m22;
			(*this)[3][2] = m23;

			// ������
			(*this)[0][3] = m30;
			(*this)[1][3] = m31;
			(*this)[2][3] = m32;
			(*this)[3][3] = m33;
		}

		// ��λ����
		Matrix4 IdentityMatrix();

		// ����
		Matrix4 ScaleMatrix(const Vector3& r);

		// ƽ��
		Matrix4 TranslationMatrix(const Vector3& r);

		// ŷ������ת
		Matrix4 RotationEulerMatrix(float rotateX, float rotateY, float rotateZ);

		Matrix4 RotationFromVectorsMatrix(const Vector3& n, const Vector3& v, const Vector3& u);

		// ��������ת
		Matrix4 RotationFromDirectionMatrix(const Vector3& forward, const Vector3& up);

		// Camera
		Matrix4 CameraMatrix(const Vector3& forward, const Vector3& up);

		// ͸��
		Matrix4 PerspectiveMatrix(float fov, float aspectRatio, float zNear, float zFar);

		// ����
		Matrix4 OrthographicMatrix(float left, float right, float bottom, float top, float near, float far);

		// ת��
		Matrix4 Transpose() const;

		// ����
		Matrix4 Inverse() const;

		// ������
		Vector4 operator*(const Vector4& r) const;
		Matrix4 operator*(const Matrix4& r) const;

		bool operator==(const Matrix4& r) const;
		bool operator!=(const Matrix4& r) const;

		friend std::ostream& operator<<(std::ostream& stream, const Matrix4& matrix);

		inline void Set(unsigned int x, unsigned int y, float val) { m[x][y] = val; }
		inline const float* operator[](int index) const { return m[index]; }
		inline float* operator[](int index) { return m[index]; }
	private:
		float m[4][4];
	};
}