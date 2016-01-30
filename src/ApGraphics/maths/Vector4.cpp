#include "Vector4.h"

namespace apanoo {
	float Vector4::Dot(const Vector4& r) const
	{
		float result = 0.0f;
		for (unsigned int i = 0; i < 4; i++)
		{
			result += (*this)[i] * r[i];
		}

		return result;
	}

	float Vector4::Max() const
	{
		float maxVal = (*this)[0];

		for (unsigned int i = 0; i < 4; i++)
		{
			if ((*this)[i] > maxVal)
			{
				maxVal = (*this)[i];
			}
		}
		return maxVal;
	}

	float Vector4::LengthSq() const
	{
		return this->Dot(*this);
	}

	float Vector4::Length() const
	{
		return sqrt(LengthSq());
	}

	Vector4 Vector4::Normalized() const
	{
		return *this / Length();
	}

	Vector4 Vector4::Lerp(const Vector4& r, float lerpFactor) const
	{
		return (r - *this) * lerpFactor + *this;
	}

	// R = L - 2 (L.dot(n)n)
	// normal 必须为单位向量
	Vector4 Vector4::Reflect(const Vector4& normal) const
	{
		return *this - (normal * (this->Dot(normal) * 2));
	}

	Vector4 Vector4::operator+(const Vector4& r) const
	{
		Vector4 result;
		for (unsigned int i = 0; i < 4; i++)
		{
			result[i] = m_Values[i] + r[i];
		}

		return result;
	}

	Vector4 Vector4::operator-(const Vector4& r) const
	{
		Vector4 result;
		for (unsigned int i = 0; i < 4; i++)
		{
			result[i] = m_Values[i] - r[i];
		}

		return result;
	}

	Vector4 Vector4::operator*(const float& r) const
	{
		Vector4 result;
		for (unsigned int i = 0; i < 4; i++)
		{
			result[i] = m_Values[i] * r;
		}

		return result;
	}

	Vector4 Vector4::operator/(const float& r) const
	{
		Vector4 result;
		for (unsigned int i = 0; i < 4; i++)
		{
			result[i] = m_Values[i] / r;
		}

		return result;
	}

	Vector4& Vector4::operator/=(const float& r)
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			(*this)[i] = m_Values[i] / r;
		}

		return *this;
	}

	bool Vector4::operator!=(const Vector4& r) const
	{
		return !operator==(r);
	}

	bool Vector4::operator==(const Vector4& r) const
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			if ((*this)[i] != r[i])
			{
				return false;
			}
		}
		return true;
	}

	Vector4& Vector4::operator*=(const float& r)
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			(*this)[i] = m_Values[i] * r;
		}

		return *this;
	}

	Vector4& Vector4::operator-=(const Vector4& r)
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			(*this)[i] = m_Values[i] - r[i];
		}

		return *this;
	}

	Vector4& Vector4::operator+=(const Vector4& r)
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			(*this)[i] = m_Values[i] + r[i];
		}

		return *this;
	}

	std::ostream& operator<<(std::ostream& stream, const Vector4& vector)
	{
		stream << "Vector4(" << vector.GetX() << "," << vector.GetY() << "," << vector.GetZ() << "," << vector.GetW() << ")";
		return stream;
	}
}