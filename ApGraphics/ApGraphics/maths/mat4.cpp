#include "mat4.h"

namespace apanoo {
	Mat4::Mat4()
	{
		for (int i = 0; i < 4 * 4; ++i)
		{
			elements[i] = 0.0f;
		}
	}

	Mat4::Mat4(float diagonal)
	{
		for (int i = 0; i < 4 * 4; ++i)
		{
			elements[i] = 0.0f;
		}

		elements[0 + 0 * 4] = diagonal;
		elements[1 + 1 * 4] = diagonal;
		elements[2 + 2 * 4] = diagonal;
		elements[3 + 3 * 4] = diagonal;
	}

	Mat4& Mat4::multiply(const Mat4& other)
	{
		float data[16];
		for (int y = 0; y < 4; ++y)
		{
			for (int x = 0; x < 4; ++x)
			{
				float sum = 0.0f;
				for (int e = 0; e < 4; ++e)
				{
					sum += elements[x + e * 4] * other.elements[e + y * 4];
				}
				data[x + y * 4] = sum;
			}
		}
		memcpy(elements, data, 4 * 4 * sizeof(float));

		return *this;
	}

	Vec3 Mat4::multiply(const Vec3& vec) const
	{
		return Vec3(
			columns[0].x * vec.x + columns[1].x * vec.y + columns[2].x * vec.z + columns[3].x,
			columns[0].y * vec.x + columns[1].y * vec.y + columns[2].y * vec.z + columns[3].y,
			columns[0].z * vec.x + columns[1].z * vec.y + columns[2].z * vec.z + columns[3].z
			);
	}

	Vec4 Mat4::multiply(const Vec4& vec) const
	{
		return Vec4(
			columns[0].x * vec.x + columns[1].x * vec.y + columns[2].x * vec.z + columns[3].x * vec.w,
			columns[0].y * vec.x + columns[1].y * vec.y + columns[2].y * vec.z + columns[3].y * vec.w,
			columns[0].z * vec.x + columns[1].z * vec.y + columns[2].z * vec.z + columns[3].z * vec.w,
			columns[0].w * vec.x + columns[1].w * vec.y + columns[2].w * vec.z + columns[3].w * vec.w
			);
	}

	// ��������
	Mat4& Mat4::invert()
	{
		double temp[16];

		temp[0] = elements[5] * elements[10] * elements[15] -
			elements[5] * elements[11] * elements[14] -
			elements[9] * elements[6] * elements[15] +
			elements[9] * elements[7] * elements[14] +
			elements[13] * elements[6] * elements[11] -
			elements[13] * elements[7] * elements[10];

		temp[4] = -elements[4] * elements[10] * elements[15] +
			elements[4] * elements[11] * elements[14] +
			elements[8] * elements[6] * elements[15] -
			elements[8] * elements[7] * elements[14] -
			elements[12] * elements[6] * elements[11] +
			elements[12] * elements[7] * elements[10];

		temp[8] = elements[4] * elements[9] * elements[15] -
			elements[4] * elements[11] * elements[13] -
			elements[8] * elements[5] * elements[15] +
			elements[8] * elements[7] * elements[13] +
			elements[12] * elements[5] * elements[11] -
			elements[12] * elements[7] * elements[9];

		temp[12] = -elements[4] * elements[9] * elements[14] +
			elements[4] * elements[10] * elements[13] +
			elements[8] * elements[5] * elements[14] -
			elements[8] * elements[6] * elements[13] -
			elements[12] * elements[5] * elements[10] +
			elements[12] * elements[6] * elements[9];

		temp[1] = -elements[1] * elements[10] * elements[15] +
			elements[1] * elements[11] * elements[14] +
			elements[9] * elements[2] * elements[15] -
			elements[9] * elements[3] * elements[14] -
			elements[13] * elements[2] * elements[11] +
			elements[13] * elements[3] * elements[10];

		temp[5] = elements[0] * elements[10] * elements[15] -
			elements[0] * elements[11] * elements[14] -
			elements[8] * elements[2] * elements[15] +
			elements[8] * elements[3] * elements[14] +
			elements[12] * elements[2] * elements[11] -
			elements[12] * elements[3] * elements[10];

		temp[9] = -elements[0] * elements[9] * elements[15] +
			elements[0] * elements[11] * elements[13] +
			elements[8] * elements[1] * elements[15] -
			elements[8] * elements[3] * elements[13] -
			elements[12] * elements[1] * elements[11] +
			elements[12] * elements[3] * elements[9];

		temp[13] = elements[0] * elements[9] * elements[14] -
			elements[0] * elements[10] * elements[13] -
			elements[8] * elements[1] * elements[14] +
			elements[8] * elements[2] * elements[13] +
			elements[12] * elements[1] * elements[10] -
			elements[12] * elements[2] * elements[9];

		temp[2] = elements[1] * elements[6] * elements[15] -
			elements[1] * elements[7] * elements[14] -
			elements[5] * elements[2] * elements[15] +
			elements[5] * elements[3] * elements[14] +
			elements[13] * elements[2] * elements[7] -
			elements[13] * elements[3] * elements[6];

		temp[6] = -elements[0] * elements[6] * elements[15] +
			elements[0] * elements[7] * elements[14] +
			elements[4] * elements[2] * elements[15] -
			elements[4] * elements[3] * elements[14] -
			elements[12] * elements[2] * elements[7] +
			elements[12] * elements[3] * elements[6];

		temp[10] = elements[0] * elements[5] * elements[15] -
			elements[0] * elements[7] * elements[13] -
			elements[4] * elements[1] * elements[15] +
			elements[4] * elements[3] * elements[13] +
			elements[12] * elements[1] * elements[7] -
			elements[12] * elements[3] * elements[5];

		temp[14] = -elements[0] * elements[5] * elements[14] +
			elements[0] * elements[6] * elements[13] +
			elements[4] * elements[1] * elements[14] -
			elements[4] * elements[2] * elements[13] -
			elements[12] * elements[1] * elements[6] +
			elements[12] * elements[2] * elements[5];

		temp[3] = -elements[1] * elements[6] * elements[11] +
			elements[1] * elements[7] * elements[10] +
			elements[5] * elements[2] * elements[11] -
			elements[5] * elements[3] * elements[10] -
			elements[9] * elements[2] * elements[7] +
			elements[9] * elements[3] * elements[6];

		temp[7] = elements[0] * elements[6] * elements[11] -
			elements[0] * elements[7] * elements[10] -
			elements[4] * elements[2] * elements[11] +
			elements[4] * elements[3] * elements[10] +
			elements[8] * elements[2] * elements[7] -
			elements[8] * elements[3] * elements[6];

		temp[11] = -elements[0] * elements[5] * elements[11] +
			elements[0] * elements[7] * elements[9] +
			elements[4] * elements[1] * elements[11] -
			elements[4] * elements[3] * elements[9] -
			elements[8] * elements[1] * elements[7] +
			elements[8] * elements[3] * elements[5];

		temp[15] = elements[0] * elements[5] * elements[10] -
			elements[0] * elements[6] * elements[9] -
			elements[4] * elements[1] * elements[10] +
			elements[4] * elements[2] * elements[9] +
			elements[8] * elements[1] * elements[6] -
			elements[8] * elements[2] * elements[5];

		double determinant = elements[0] * temp[0] + elements[1] * temp[4] + elements[2] * temp[8] + elements[3] * temp[12];
		determinant = 1.0 / determinant;

		for (int i = 0; i < 4 * 4; i++)
			elements[i] = (float)(temp[i] * determinant);

		return *this;
	}

	Mat4 Mat4::identity()
	{
		return Mat4(1.0f);
	}

	// �ѵ�
	apanoo::Mat4 Mat4::camera(const Vec3& forward, const Vec3& up)
	{
		Mat4 result = Mat4(1.0);
		Vec3 f = forward;
		f.normalize();

		Vec3 r = up;
		r.normalize();

		r = r.cross(f);

		Vec3 u = f.cross(r);

		// ��һ��
		result.elements[0 + 0 * 4] = r.x;
		result.elements[0 + 1 * 4] = u.x;
		result.elements[0 + 2 * 4] = f.x;
		
		// �ڶ���
		result.elements[1 + 0 * 4] = r.y;
		result.elements[1 + 1 * 4] = u.y;
		result.elements[1 + 2 * 4] = f.y;

		// ������
		result.elements[2 + 0 * 4] = r.z;
		result.elements[2 + 1 * 4] = u.z;
		result.elements[2 + 2 * 4] = f.z;

		return result;
	}

	// �ѵ�1��������ͼ����
	Mat4 Mat4::orthographic(float left, float right, float bottom, float top, float near, float far)
	{
		Mat4 result(1.0f);

		result.elements[0 + 0 * 4] = 2.0f / (right - left);
		result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
		result.elements[2 + 2 * 4] = 2.0f / (near - far);

		result.elements[0 + 3 * 4] = (left + right) / (left - right);
		result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
		result.elements[2 + 3 * 4] = (far + near) / (far - near);

		return result;
	}

	apanoo::Mat4 Mat4::projection(float fov, float width, float height, float near, float far)
	{
		Mat4 result = Mat4(1.0);
		float ar = (float)((float)width / (float)height);
		float tanHalfFOV = (float)tan(toRadians(fov / 2));
		float zRange = near - far;

		// ��һ��
		result.elements[0 + 0 * 4] = 1.0f / (tanHalfFOV * ar);

		// �ڶ���
		result.elements[1 + 1 * 4] = 1.0f / tanHalfFOV;

		// ������
		result.elements[2 + 2 * 4] = (-near - far) / zRange;
		result.elements[2 + 3 * 4] = -1;

		// ������
		result.elements[3 + 2 * 4] = 2 * far * near / zRange;

		return result;

		/*Mat4 result(1.0f);
		float aspectRatio = (float)width / (float)height;

		float q = 1.0f / tan(toRadians(0.5f * fov));
		float a = q / aspectRatio;

		float b = (near + far) / (near - far);
		float c = (2.0f * near * far) / (near - far);

		result.elements[0 + 0 * 4] = a;
		result.elements[1 + 1 * 4] = q;
		result.elements[2 + 2 * 4] = b;
		result.elements[3 + 2 * 4] = -1.0f;
		result.elements[2 + 3 * 4] = c;

		return result;*/
	}

	// ��������嵱ǰλ�ý���ƽ��
	Mat4 Mat4::translation(const Vec3& translation)
	{
		Mat4 result(1.0f);

		result.elements[0 + 3 * 4] = translation.x;
		result.elements[1 + 3 * 4] = translation.y;
		result.elements[2 + 3 * 4] = translation.z;

		return result;
	}

	// �ѵ�3 ; Ŀǰ������ڵ�ǰ����ϵԭ����ת���������������������ת
	Mat4 Mat4::rotation(float angle, const Vec3& axis)
	{
		Mat4 result(1.0f);

		float r = toRadians(angle);
		float c = cos(r);
		float s = sin(r);

		float omc = 1.0f - c;

		float x = axis.x;
		float y = axis.y;
		float z = axis.z;

		result.elements[0 + 0 * 4] = x * omc + c;
		result.elements[1 + 0 * 4] = y * x * omc + z * s;
		result.elements[2 + 0 * 4] = x * z * omc - y * s;

		result.elements[0 + 1 * 4] = x * y * omc - z * s;
		result.elements[1 + 1 * 4] = y * omc + c;
		result.elements[2 + 1 * 4] = y * z * omc + x * s;

		result.elements[0 + 2 * 4] = x * z * omc + y * s;
		result.elements[1 + 2 * 4] = y * z * omc - x * s;
		result.elements[2 + 2 * 4] = z * omc + c;

		return result;
	}

	apanoo::Mat4 Mat4::rotation(float x, float y, float z)
	{
		Mat4 a = rotation(x, Vec3(1, 0, 0));
		Mat4 b = rotation(y, Vec3(0, 1, 0));
		Mat4 c = rotation(z, Vec3(0, 0, 1));
		return a * b * c;
	}

	// Ŀǰ������ڵ�ǰ����ϵԭ�����������������������ķ���
	Mat4 Mat4::scale(const Vec3& scale)
	{
		Mat4 result(1.0f);

		result.elements[0 + 0 * 4] = scale.x;
		result.elements[1 + 1 * 4] = scale.y;
		result.elements[2 + 2 * 4] = scale.z;

		return result;
	}

	Mat4 Mat4::operator*=(const Mat4& other)
	{
		return multiply(other);
	}

	Mat4 operator*(Mat4& left, const Mat4& right)
	{
		Mat4 resultLeft;
		memcpy(resultLeft.elements, left.elements, 4 * 4 * sizeof(float));
		return resultLeft.multiply(right);
		// return left.multiply(right);
	}

	Vec3 operator*(const Mat4& left, const Vec3& right)
	{
		Mat4 resultLeft;
		memcpy(resultLeft.elements, left.elements, 4 * 4 * sizeof(float));
		return resultLeft.multiply(right);
		// return left.multiply(right);
	}

	Vec4 operator*(const Mat4& left, const Vec4& right)
	{
		Mat4 resultLeft;
		memcpy(resultLeft.elements, left.elements, 4 * 4 * sizeof(float));
		return resultLeft.multiply(right);
		// return left.multiply(right);
	}
}