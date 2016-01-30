#include "Matrix4.h"

namespace apanoo {
	Matrix4 Matrix4::IdentityMatrix()
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				if (i == j)
					m[i][j] = 1.0f;
				else
					m[i][j] = 0.0f;
			}
		}

		return *this;
	}

	Matrix4 Matrix4::ScaleMatrix(const Vector3& r)
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				if (i == j && i != 4 - 1)
					m[i][j] = r[i];
				else
					m[i][j] = 0.0f;
			}
		}

		m[4 - 1][4 - 1] = 1.0f;

		return *this;
	}

	Matrix4 Matrix4::TranslationMatrix(const Vector3& r)
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				if (i == 4 - 1 && j != 4 - 1)
					m[i][j] = r[j];
				else if (i == j)
					m[i][j] = 1.0f;
				else
					m[i][j] = 0.0f;
			}
		}

		m[4 - 1][4 - 1] = 1.0f;

		return *this;
	}

	Matrix4 Matrix4::RotationEulerMatrix(float rotateX, float rotateY, float rotateZ)
	{
		Matrix4 rx, ry, rz;

		const float x = rotateX;
		const float y = rotateY;
		const float z = rotateZ;

		// 绕x轴旋转rotateX度
		rx[0][0] = 1.0f;   rx[1][0] = 0.0f;    rx[2][0] = 0.0f;    rx[3][0] = 0.0f;
		rx[0][1] = 0.0f;   rx[1][1] = cos(x);  rx[2][1] = -sin(x); rx[3][1] = 0.0f;
		rx[0][2] = 0.0f;   rx[1][2] = sin(x);  rx[2][2] = cos(x);  rx[3][2] = 0.0f;
		rx[0][3] = 0.0f;   rx[1][3] = 0.0f;    rx[2][3] = 0.0f;    rx[3][3] = 1.0f;

		// 绕y轴旋转rotateY度
		ry[0][0] = cos(y); ry[1][0] = 0.0f;    ry[2][0] = -sin(y); ry[3][0] = 0.0f;
		ry[0][1] = 0.0f;   ry[1][1] = 1.0f;    ry[2][1] = 0.0f;    ry[3][1] = 0.0f;
		ry[0][2] = sin(y); ry[1][2] = 0.0f;    ry[2][2] = cos(y);  ry[3][2] = 0.0f;
		ry[0][3] = 0.0f;   ry[1][3] = 0.0f;    ry[2][3] = 0.0f;    ry[3][3] = 1.0f;

		// 绕z轴旋转rotateZ度
		rz[0][0] = cos(z); rz[1][0] = -sin(z); rz[2][0] = 0.0f;    rz[3][0] = 0.0f;
		rz[0][1] = sin(z); rz[1][1] = cos(z);  rz[2][1] = 0.0f;    rz[3][1] = 0.0f;
		rz[0][2] = 0.0f;   rz[1][2] = 0.0f;    rz[2][2] = 1.0f;    rz[3][2] = 0.0f;
		rz[0][3] = 0.0f;   rz[1][3] = 0.0f;    rz[2][3] = 0.0f;    rz[3][3] = 1.0f;

		*this = rz * ry * rx;

		return *this;
	}

	Matrix4 Matrix4::RotationFromVectorsMatrix(const Vector3& n, const Vector3& v, const Vector3& u)
	{
		(*this)[0][0] = u.GetX();   (*this)[1][0] = u.GetY();   (*this)[2][0] = u.GetZ();   (*this)[3][0] = 0.0f;
		(*this)[0][1] = v.GetX();   (*this)[1][1] = v.GetY();   (*this)[2][1] = v.GetZ();   (*this)[3][1] = 0.0f;
		(*this)[0][2] = n.GetX();   (*this)[1][2] = n.GetY();   (*this)[2][2] = n.GetZ();   (*this)[3][2] = 0.0f;
		(*this)[0][3] = 0.0f;       (*this)[1][3] = 0.0f;       (*this)[2][3] = 0.0f;       (*this)[3][3] = 1.0f;

		return *this;
	}

	Matrix4 Matrix4::RotationFromDirectionMatrix(const Vector3& forward, const Vector3& up)
	{
		Vector3 n = forward.Normalized();
		Vector3 u = Vector3(up.Normalized()).Cross(n);
		Vector3 v = n.Cross(u);

		return RotationFromVectorsMatrix(n, v, u);
	}

	Matrix4 Matrix4::CameraMatrix(const Vector3& forward, const Vector3& up)
	{
		Vector3 f = forward;
		f = f.Normalized();

		Vector3 r = up;
		r = r.Normalized();
		r = r.Cross(f);

		Vector3 u = f.Cross(r);

		(*this)[0][0] = r.GetX();   (*this)[1][0] = r.GetY();   (*this)[2][0] = r.GetZ();	(*this)[3][0] = 0.0f;
		(*this)[0][1] = u.GetX();	(*this)[1][1] = u.GetY();	(*this)[2][1] = u.GetZ();	(*this)[3][1] = 0.0f;
		(*this)[0][2] = f.GetX();	(*this)[1][2] = f.GetY();	(*this)[2][2] = f.GetZ();	(*this)[3][2] = 0.0f;
		(*this)[0][3] = 0.0f;		(*this)[1][3] = 0.0f;		(*this)[2][3] = 0.0f;		(*this)[3][3] = 1.0f;

		return *this;
	}

	Matrix4 Matrix4::PerspectiveMatrix(float fov, float aspectRatio, float zNear, float zFar)
	{
		const float zRange = zNear - zFar;
		const float tanHalfFOV = tanf(fov / 2.0f);

		(*this)[0][0] = 1.0f / (tanHalfFOV * aspectRatio); (*this)[1][0] = 0.0f;			  (*this)[2][0] = 0.0f;						(*this)[3][0] = 0.0f;
		(*this)[0][1] = 0.0f;							   (*this)[1][1] = 1.0f / tanHalfFOV; (*this)[2][1] = 0.0f;						(*this)[3][1] = 0.0f;
		(*this)[0][2] = 0.0f;							   (*this)[1][2] = 0.0f;              (*this)[2][2] = (-zNear - zFar) / zRange; (*this)[3][2] = 2.0f*zFar*zNear / zRange;
		(*this)[0][3] = 0.0f;							   (*this)[1][3] = 0.0f;              (*this)[2][3] = 1.0f;						(*this)[3][3] = 0.0f;

		return *this;
	}

	Matrix4 Matrix4::OrthographicMatrix(float left, float right, float bottom, float top, float near, float far)
	{
		const float width = (right - left);
		const float height = (top - bottom);
		const float depth = (far - near);

		(*this)[0][0] = 2.0f / width; (*this)[1][0] = 0.0f;          (*this)[2][0] = 0.0f;          (*this)[3][0] = -(right + left) / width;
		(*this)[0][1] = 0.0f;         (*this)[1][1] = 2.0f / height; (*this)[2][1] = 0.0f;          (*this)[3][1] = -(top + bottom) / height;
		(*this)[0][2] = 0.0f;         (*this)[1][2] = 0.0f;          (*this)[2][2] = -2.0f / depth; (*this)[3][2] = -(far + near) / depth;
		(*this)[0][3] = 0.0f;         (*this)[1][3] = 0.0f;          (*this)[2][3] = 0.0f;          (*this)[3][3] = 1.0f;

		return *this;
	}

	Matrix4 Matrix4::Transpose() const
	{
		Matrix4 t;
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 4; i++) {
				t[i][j] = m[j][i];
			}
		}
		return t;
	}

	// 求逆矩阵
	Matrix4 Matrix4::Inverse() const
	{
		// 求伴随矩阵
		Matrix4 result;
		result[0][0] = (*this)[1][1] * (*this)[2][2] * (*this)[3][3] -
			(*this)[1][1] * (*this)[2][3] * (*this)[3][2] -
			(*this)[2][1] * (*this)[1][2] * (*this)[3][3] +
			(*this)[2][1] * (*this)[1][3] * (*this)[3][2] +
			(*this)[3][1] * (*this)[1][2] * (*this)[2][3] -
			(*this)[3][1] * (*this)[1][3] * (*this)[2][2];

		result[1][0] = -(*this)[1][0] * (*this)[2][2] * (*this)[3][3] +
			(*this)[1][0] * (*this)[2][3] * (*this)[3][2] +
			(*this)[2][0] * (*this)[1][2] * (*this)[3][3] -
			(*this)[2][0] * (*this)[1][3] * (*this)[3][2] -
			(*this)[3][0] * (*this)[1][2] * (*this)[2][3] +
			(*this)[3][0] * (*this)[1][3] * (*this)[2][2];

		result[2][0] = (*this)[1][0] * (*this)[2][1] * (*this)[3][3] -
			(*this)[1][0] * (*this)[2][3] * (*this)[3][1] -
			(*this)[2][0] * (*this)[1][1] * (*this)[3][3] +
			(*this)[2][0] * (*this)[1][3] * (*this)[3][1] +
			(*this)[3][0] * (*this)[1][1] * (*this)[2][3] -
			(*this)[3][0] * (*this)[1][3] * (*this)[2][1];

		result[3][0] = -(*this)[1][0] * (*this)[2][1] * (*this)[3][2] +
			(*this)[1][0] * (*this)[2][2] * (*this)[3][1] +
			(*this)[2][0] * (*this)[1][1] * (*this)[3][2] -
			(*this)[2][0] * (*this)[1][2] * (*this)[3][1] -
			(*this)[3][0] * (*this)[1][1] * (*this)[2][2] +
			(*this)[3][0] * (*this)[1][2] * (*this)[2][1];

		result[0][1] = -(*this)[0][1] * (*this)[2][2] * (*this)[3][3] +
			(*this)[0][1] * (*this)[2][3] * (*this)[3][2] +
			(*this)[2][1] * (*this)[0][2] * (*this)[3][3] -
			(*this)[2][1] * (*this)[0][3] * (*this)[3][2] -
			(*this)[3][1] * (*this)[0][2] * (*this)[2][3] +
			(*this)[3][1] * (*this)[0][3] * (*this)[2][2];

		result[1][1] = (*this)[0][0] * (*this)[2][2] * (*this)[3][3] -
			(*this)[0][0] * (*this)[2][3] * (*this)[3][2] -
			(*this)[2][0] * (*this)[0][2] * (*this)[3][3] +
			(*this)[2][0] * (*this)[0][3] * (*this)[3][2] +
			(*this)[3][0] * (*this)[0][2] * (*this)[2][3] -
			(*this)[3][0] * (*this)[0][3] * (*this)[2][2];

		result[2][1] = -(*this)[0][0] * (*this)[2][1] * (*this)[3][3] +
			(*this)[0][0] * (*this)[2][3] * (*this)[3][1] +
			(*this)[2][0] * (*this)[0][1] * (*this)[3][3] -
			(*this)[2][0] * (*this)[0][3] * (*this)[3][1] -
			(*this)[3][0] * (*this)[0][1] * (*this)[2][3] +
			(*this)[3][0] * (*this)[0][3] * (*this)[2][1];

		result[3][1] = (*this)[0][0] * (*this)[2][1] * (*this)[3][2] -
			(*this)[0][0] * (*this)[2][2] * (*this)[3][1] -
			(*this)[2][0] * (*this)[0][1] * (*this)[3][2] +
			(*this)[2][0] * (*this)[0][2] * (*this)[3][1] +
			(*this)[3][0] * (*this)[0][1] * (*this)[2][2] -
			(*this)[3][0] * (*this)[0][2] * (*this)[2][1];

		result[0][2] = (*this)[0][1] * (*this)[1][2] * (*this)[3][3] -
			(*this)[0][1] * (*this)[1][3] * (*this)[3][2] -
			(*this)[1][1] * (*this)[0][2] * (*this)[3][3] +
			(*this)[1][1] * (*this)[0][3] * (*this)[3][2] +
			(*this)[3][1] * (*this)[0][2] * (*this)[1][3] -
			(*this)[3][1] * (*this)[0][3] * (*this)[1][2];

		result[1][2] = -(*this)[0][0] * (*this)[1][2] * (*this)[3][3] +
			(*this)[0][0] * (*this)[1][3] * (*this)[3][2] +
			(*this)[1][0] * (*this)[0][2] * (*this)[3][3] -
			(*this)[1][0] * (*this)[0][3] * (*this)[3][2] -
			(*this)[3][0] * (*this)[0][2] * (*this)[1][3] +
			(*this)[3][0] * (*this)[0][3] * (*this)[1][2];

		result[2][2] = (*this)[0][0] * (*this)[1][1] * (*this)[3][3] -
			(*this)[0][0] * (*this)[1][3] * (*this)[3][1] -
			(*this)[1][0] * (*this)[0][1] * (*this)[3][3] +
			(*this)[1][0] * (*this)[0][3] * (*this)[3][1] +
			(*this)[3][0] * (*this)[0][1] * (*this)[1][3] -
			(*this)[3][0] * (*this)[0][3] * (*this)[1][1];

		result[3][2] = -(*this)[0][0] * (*this)[1][1] * (*this)[3][2] +
			(*this)[0][0] * (*this)[1][2] * (*this)[3][1] +
			(*this)[1][0] * (*this)[0][1] * (*this)[3][2] -
			(*this)[1][0] * (*this)[0][2] * (*this)[3][1] -
			(*this)[3][0] * (*this)[0][1] * (*this)[1][2] +
			(*this)[3][0] * (*this)[0][2] * (*this)[1][1];

		result[0][3] = -(*this)[0][1] * (*this)[1][2] * (*this)[2][3] +
			(*this)[0][1] * (*this)[1][3] * (*this)[2][2] +
			(*this)[1][1] * (*this)[0][2] * (*this)[2][3] -
			(*this)[1][1] * (*this)[0][3] * (*this)[2][2] -
			(*this)[2][1] * (*this)[0][2] * (*this)[1][3] +
			(*this)[2][1] * (*this)[0][3] * (*this)[1][2];

		result[1][3] = (*this)[0][0] * (*this)[1][2] * (*this)[2][3] -
			(*this)[0][0] * (*this)[1][3] * (*this)[2][2] -
			(*this)[1][0] * (*this)[0][2] * (*this)[2][3] +
			(*this)[1][0] * (*this)[0][3] * (*this)[2][2] +
			(*this)[2][0] * (*this)[0][2] * (*this)[1][3] -
			(*this)[2][0] * (*this)[0][3] * (*this)[1][2];

		result[2][3] = -(*this)[0][0] * (*this)[1][1] * (*this)[2][3] +
			(*this)[0][0] * (*this)[1][3] * (*this)[2][1] +
			(*this)[1][0] * (*this)[0][1] * (*this)[2][3] -
			(*this)[1][0] * (*this)[0][3] * (*this)[2][1] -
			(*this)[2][0] * (*this)[0][1] * (*this)[1][3] +
			(*this)[2][0] * (*this)[0][3] * (*this)[1][1];

		result[3][3] = (*this)[0][0] * (*this)[1][1] * (*this)[2][2] -
			(*this)[0][0] * (*this)[1][2] * (*this)[2][1] -
			(*this)[1][0] * (*this)[0][1] * (*this)[2][2] +
			(*this)[1][0] * (*this)[0][2] * (*this)[2][1] +
			(*this)[2][0] * (*this)[0][1] * (*this)[1][2] -
			(*this)[2][0] * (*this)[0][2] * (*this)[1][1];

		// 行列式值
		float determinant = (*this)[0][0] * result[0][0] + (*this)[0][1] * result[1][0] + (*this)[0][2] * result[2][0] + (*this)[0][3] * result[3][0];
		determinant = 1.0f / determinant;

		// 求逆矩阵元素
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				result[i][j] = result[i][j] * determinant;
				if (result[i][j] >= 0)
				{
					result[i][j] = abs(result[i][j]);
				}
			}
		}
		return result;
	}

	Matrix4 Matrix4::operator*(const Matrix4& r) const
	{
		Matrix4 ret;
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				ret.m[i][j] = 0.0f;
				for (unsigned int k = 0; k < 4; k++)
				{
					ret.m[i][j] += m[k][j] * r.m[i][k];
				}
			}
		}
		return ret;
	}

	Vector4 Matrix4::operator*(const Vector4& r) const
	{
		Vector4 result;

		for (unsigned int i = 0; i < 4; i++)
		{
			result[i] = 0;
			for (unsigned int j = 0; j < 4; j++)
			{
				result[i] += m[j][i] * r[j];
			}
		}

		return result;
	}

	bool Matrix4::operator!=(const Matrix4& r) const
	{
		return !operator==(r);
	}

	bool Matrix4::operator==(const Matrix4& r) const
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				if ((*this)[i][j] != r[i][j])
				{
					return false;
				}
			}
		}
		return true;
	}

	std::ostream& operator<<(std::ostream& stream, const Matrix4& matrix)
	{
		for (unsigned int j = 0; j < 4; j++)
		{
			for (unsigned int i = 0; i < 4; i++)
			{
				stream << matrix[i][j] << "  ";
			}
			stream << std::endl;
		}
		return stream;
	}
}