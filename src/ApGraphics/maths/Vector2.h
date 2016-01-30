#pragma once
#include "MathTools.h"

namespace apanoo {
	class Vector2
	{
	public:
		Vector2() { }

		Vector2(const Vector2& r)
		{
			(*this)[0] = r[0];
			(*this)[1] = r[1];
		}

		Vector2(float x, float y)
		{
			(*this)[0] = x;
			(*this)[1] = y;
		}

		inline float GetX() const { return (*this)[0]; }
		inline float GetY() const { return (*this)[1]; }
		inline void SetX(const float& x) { (*this)[0] = x; }
		inline void SetY(const float& y) { (*this)[1] = y; }
		inline void Set(const float& x, const float& y) { SetX(x); SetY(y); }

		// ���
		float Cross(const Vector2& r) const;

		// ���
		float Dot(const Vector2& r) const;

		// ������
		float Max() const;

		// ���ȵ�ƽ��
		float LengthSq() const;

		// ����
		float Length() const;

		// ��λ��
		Vector2 Normalized() const;

		// ���Բ�ֵ��this��r֮������Բ�ֵ��lerpFactor��Χ��[0, 1]
		Vector2 Lerp(const Vector2& r, float lerpFactor) const;

		// ���淴�䣬normalΪ����
		Vector2 Reflect(const Vector2& normal) const;

		Vector2 operator+(const Vector2& r) const;
		Vector2 operator-(const Vector2& r) const;
		Vector2 operator*(const float& r) const;
		Vector2 operator/(const float& r) const;

		Vector2& operator+=(const Vector2& r);
		Vector2& operator-=(const Vector2& r);
		Vector2& operator*=(const float& r);
		Vector2& operator/=(const float& r);

		bool operator==(const Vector2& r) const;
		bool operator!=(const Vector2& r) const;

		friend std::ostream& operator<<(std::ostream& stream, const Vector2& vector);

		// �޸�values
		inline float& operator [] (unsigned int i) { return m_Values[i]; }
		// ����values
		inline float operator [] (unsigned int i) const { return m_Values[i]; }

	private:
		float m_Values[2];
	};
}