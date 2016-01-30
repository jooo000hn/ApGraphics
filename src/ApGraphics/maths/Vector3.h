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

		// 叉积
		Vector3 Cross(const Vector3& r) const;

		// 点积
		float Dot(const Vector3& r) const;

		// 最大分量
		float Max() const;

		// 长度的平方
		float LengthSq() const;

		// 长度
		float Length() const;

		// 旋转（通过旋转轴与旋转角）
		Vector3 Rotate(float angle, const Vector3& axis) const;

		// 旋转（通过四元数）
		Vector3 Rotate(const Quaternion& rotation) const;

		// 单位化
		Vector3 Normalized() const;

		// 线性插值，this与r之间的线性插值，lerpFactor范围：[0, 1]
		Vector3 Lerp(const Vector3& r, float lerpFactor) const;

		// 镜面反射，normal为法线
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

		// 修改values
		inline float& operator [] (unsigned int i) { return m_Values[i]; }
		// 访问values
		inline float operator [] (unsigned int i) const { return m_Values[i]; }

	private:
		float m_Values[3];
	};
}