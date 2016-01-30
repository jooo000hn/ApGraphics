#pragma once
#include "MathTools.h"

namespace apanoo {
	class Quaternion;

	class Vector3
	{
	public:
		Vector3() { }

		Vector3(const Vector3& r)
		{
			(*this)[0] = r[0];
			(*this)[1] = r[1];
			(*this)[2] = r[2];
		}

		Vector3(float x, float y, float z)
		{
			(*this)[0] = x;
			(*this)[1] = y;
			(*this)[2] = z;
		}

		inline float GetX() const { return (*this)[0]; }
		inline float GetY() const { return (*this)[1]; }
		inline float GetZ() const { return (*this)[2]; }
		inline void SetX(const float& x) { (*this)[0] = x; }
		inline void SetY(const float& y) { (*this)[1] = y; }
		inline void SetZ(const float& z) { (*this)[2] = z; }
		inline void Set(const float& x, const float& y, const float& z) { SetX(x); SetY(y); SetZ(z); }

		// ���
		Vector3 Cross(const Vector3& r) const;

		// ���
		float Dot(const Vector3& r) const;

		// ������
		float Max() const;

		// ���ȵ�ƽ��
		float LengthSq() const;

		// ����
		float Length() const;

		// ��ת��ͨ����ת������ת�ǣ�
		Vector3 Rotate(float angle, const Vector3& axis) const;

		// ��ת��ͨ����Ԫ����
		Vector3 Rotate(const Quaternion& rotation) const;

		// ��λ��
		Vector3 Normalized() const;

		// ���Բ�ֵ��this��r֮������Բ�ֵ��lerpFactor��Χ��[0, 1]
		Vector3 Lerp(const Vector3& r, float lerpFactor) const;

		// ���淴�䣬normalΪ����
		Vector3 Reflect(const Vector3& normal) const;

		Vector3 operator+(const Vector3& r) const;
		Vector3 operator-(const Vector3& r) const;
		Vector3 operator*(const float& r) const;
		Vector3 operator/(const float& r) const;

		Vector3& operator+=(const Vector3& r);
		Vector3& operator-=(const Vector3& r);
		Vector3& operator*=(const float& r);
		Vector3& operator/=(const float& r);

		bool operator==(const Vector3& r) const;
		bool operator!=(const Vector3& r) const;

		friend std::ostream& operator<<(std::ostream& stream, const Vector3& vector);

		// �޸�values
		inline float& operator [] (unsigned int i) { return m_Values[i]; }
		// ����values
		inline float operator [] (unsigned int i) const { return m_Values[i]; }

	private:
		float m_Values[3];
	};
}