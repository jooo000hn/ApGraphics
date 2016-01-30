#include "Vector2.h"

namespace apanoo {
	float Vector2::Cross(const Vector2& r) const
	{
		return GetX() * r.GetY() - GetY() * r.GetX();
	}

	float Vector2::Dot(const Vector2& r) const
	{
		float result = 0.0f;
		for (unsigned int i = 0; i < 2; i++)
		{
			result += (*this)[i] * r[i];
		}

		return result;
	}

	float Vector2::Max() const
	{
		float maxVal = (*this)[0];

		for (unsigned int i = 0; i < 2; i++)
		{
			if ((*this)[i] > maxVal)
			{
				maxVal = (*this)[i];
			}
		}
		return maxVal;
	}

	float Vector2::LengthSq() const
	{
		return this->Dot(*this);
	}

	float Vector2::Length() const
	{
		return sqrt(LengthSq());
	}

	Vector2 Vector2::Normalized() const
	{
		return *this / Length();
	}

	Vector2 Vector2::Lerp(const Vector2& r, float lerpFactor) const
	{
		return (r - *this) * lerpFactor + *this;
	}

	// R = L - 2 (L.dot(n)n)
	Vector2 Vector2::Reflect(const Vector2& normal) const
	{
		return *this - (normal * (this->Dot(normal) * 2));
	}

	Vector2 Vector2::operator+(const Vector2& r) const
	{
		Vector2 result;
		for (unsigned int i = 0; i < 2; i++)
		{
			result[i] = m_Values[i] + r[i];
		}

		return result;
	}

	Vector2 Vector2::operator-(const Vector2& r) const
	{
		Vector2 result;
		for (unsigned int i = 0; i < 2; i++)
		{
			result[i] = m_Values[i] - r[i];
		}

		return result;
	}

	Vector2 Vector2::operator*(const float& r) const
	{
		Vector2 result;
		for (unsigned int i = 0; i < 2; i++)
		{
			result[i] = m_Values[i] * r;
		}

		return result;
	}

	Vector2 Vector2::operator/(const float& r) const
	{
		Vector2 result;
		for (unsigned int i = 0; i < 2; i++)
		{
			result[i] = m_Values[i] / r;
		}

		return result;
	}

	Vector2& Vector2::operator/=(const float& r)
	{
		for (unsigned int i = 0; i < 2; i++)
		{
			(*this)[i] = m_Values[i] / r;
		}

		return *this;
	}

	std::ostream& operator<<(std::ostream& stream, const Vector2& vector)
	{
		stream << "Vector2(" << vector.GetX() << "," << vector.GetY() << ")";
		return stream;
	}

	bool Vector2::operator!=(const Vector2& r) const
	{
		return !operator==(r);
	}

	bool Vector2::operator==(const Vector2& r) const
	{
		for (unsigned int i = 0; i < 2; i++)
		{
			if ((*this)[i] != r[i])
			{
				return false;
			}
		}
		return true;
	}

	Vector2& Vector2::operator*=(const float& r)
	{
		for (unsigned int i = 0; i < 2; i++)
		{
			(*this)[i] = m_Values[i] * r;
		}

		return *this;
	}

	Vector2& Vector2::operator-=(const Vector2& r)
	{
		for (unsigned int i = 0; i < 2; i++)
		{
			(*this)[i] = m_Values[i] - r[i];
		}

		return *this;
	}

	Vector2& Vector2::operator+=(const Vector2& r)
	{
		for (unsigned int i = 0; i < 2; i++)
		{
			(*this)[i] = m_Values[i] + r[i];
		}

		return *this;
	}
}