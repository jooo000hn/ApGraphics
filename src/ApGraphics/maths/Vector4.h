#pragma once
#include "MathTools.h"
namespace apanoo {
	class Vector4
	{
	public:
		Vector4() { }

		Vector4(const Vector4& r)
		{
			(*this)[0] = r[0];
			(*this)[1] = r[1];
			(*this)[2] = r[2];
			(*this)[3] = r[3];
		}

		Vector4(float x, float y, float z, float w)
		{
			(*this)[0] = x;
			(*this)[1] = y;
			(*this)[2] = z;
			(*this)[3] = w;
		}

		inline float GetX() const { return (*this)[0]; }
		inline float GetY() const { return (*this)[1]; }
		inline float GetZ() const { return (*this)[2]; }
		inline float GetW() const { return (*this)[3]; }
		inline void SetX(const float& x) { (*this)[0] = x; }
		inline void SetY(const float& y) { (*this)[1] = y; }
		inline void SetZ(const float& z) { (*this)[2] = z; }
		inline void SetW(const float& w) { (*this)[3] = w; }
		inline void Set(const float& x, const float& y, const float& z, const float& w)
		{
			SetX(x);
			SetY(y);
			SetZ(z);
			SetW(w);
		}

		// ���
		float Dot(const Vector4& r) const;

		// ������
		float Max() const;

		// ���ȵ�ƽ��
		float LengthSq() const;

		// ����
		float Length() const;

		// ��λ��
		Vector4 Normalized() const;

		// ���Բ�ֵ��this��r֮������Բ�ֵ��lerpFactor��Χ��[0, 1]
		Vector4 Lerp(const Vector4& r, float lerpFactor) const;

		// ���淴�䣬normalΪ����
		Vector4 Reflect(const Vector4& normal) const;

		Vector4 operator+(const Vector4& r) const;
		Vector4 operator-(const Vector4& r) const;
		Vector4 operator*(const float& r) const;
		Vector4 operator/(const float& r) const;

		Vector4& operator+=(const Vector4& r);
		Vector4& operator-=(const Vector4& r);
		Vector4& operator*=(const float& r);
		Vector4& operator/=(const float& r);

		bool operator==(const Vector4& r) const;
		bool operator!=(const Vector4& r) const;

		friend std::ostream& operator<<(std::ostream& stream, const Vector4& vector);

		// �޸�values
		inline float& operator [] (unsigned int i) { return m_Values[i]; }
		// ����values
		inline float operator [] (unsigned int i) const { return m_Values[i]; }

	private:
		float m_Values[4];
	};
}