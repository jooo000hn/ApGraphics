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
	* 注意：m[i][j] j表示行，i表示列
	* 使用列主序主要是Shader中glUniformMatrix4fv第三参数决定
	* 使传送到shader的矩阵保持存储方式一致
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
			// 第一列
			(*this)[0][0] = m00;
			(*this)[1][0] = m01;
			(*this)[2][0] = m02;
			(*this)[3][0] = m03;

			// 第二列
			(*this)[0][1] = m10;
			(*this)[1][1] = m11;
			(*this)[2][1] = m12;
			(*this)[3][1] = m13;

			// 第三列
			(*this)[0][2] = m20;
			(*this)[1][2] = m21;
			(*this)[2][2] = m22;
			(*this)[3][2] = m23;

			// 第四列
			(*this)[0][3] = m30;
			(*this)[1][3] = m31;
			(*this)[2][3] = m32;
			(*this)[3][3] = m33;
		}

		// 单位矩阵
		Matrix4 IdentityMatrix();

		// 放缩
		Matrix4 ScaleMatrix(const Vector3& r);

		// 平移
		Matrix4 TranslationMatrix(const Vector3& r);

		// 欧拉角旋转
		Matrix4 RotationEulerMatrix(float rotateX, float rotateY, float rotateZ);

		Matrix4 RotationFromVectorsMatrix(const Vector3& n, const Vector3& v, const Vector3& u);

		// 按方向旋转
		Matrix4 RotationFromDirectionMatrix(const Vector3& forward, const Vector3& up);

		// Camera
		Matrix4 CameraMatrix(const Vector3& forward, const Vector3& up);

		// 透视
		Matrix4 PerspectiveMatrix(float fov, float aspectRatio, float zNear, float zFar);

		// 正交
		Matrix4 OrthographicMatrix(float left, float right, float bottom, float top, float near, float far);

		// 转置
		Matrix4 Transpose() const;

		// 求逆
		Matrix4 Inverse() const;

		// 操作符
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