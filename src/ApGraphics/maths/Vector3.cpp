#include "Vector3.h"
#include "Quaternion.h"

namespace apanoo {
	Vector3 Vector3::Cross(const Vector3& r) const
	{
		float x = (*this)[1] * r[2] - (*this)[2] * r[1];
		float y = (*this)[2] * r[0] - (*this)[0] * r[2];
		float z = (*this)[0] * r[1] - (*this)[1] * r[0];

		return Vector3(x, y, z);
	}

	float Vector3::Dot(const Vector3& r) const
	{
		float result = 0.0f;
		for (unsigned int i = 0; i < 3; i++)
		{
			result += (*this)[i] * r[i];
		}

		return result;
	}

	float Vector3::Max() const
	{
		float maxVal = (*this)[0];

		for (unsigned int i = 0; i < 3; i++)
		{
			if ((*this)[i] > maxVal)
			{
				maxVal = (*this)[i];
			}
		}
		return maxVal;
	}

	float Vector3::LengthSq() const
	{
		return this->Dot(*this);
	}

	float Vector3::Length() const
	{
		return sqrt(LengthSq());
	}

	Vector3 Vector3::Rotate(float angle, const Vector3& axis) const
	{
		// const float sin = sinf(-angle);
		// const float cos = cosf(-angle);

		// return this->Cross(axis * sin) +        // Rotation on local X
		//	   (*this * cos) +                     // Rotation on local Z
		//	   axis * this->Dot(axis * (1 - cos)); // Rotation on local Y

		const float sinHalfAngle = sinf(angle/2);
		const float cosHalfAngle = cosf(angle/2);

		const float Rx = axis.GetX() * sinHalfAngle;
		const float Ry = axis.GetY() * sinHalfAngle;
		const float Rz = axis.GetZ() * sinHalfAngle;
		const float Rw = cosHalfAngle;

		Quaternion rotationQ(Rx, Ry, Rz, Rw);
		Quaternion conjugateQ = rotationQ.Conjugate();
		Quaternion w = rotationQ * (*this) * conjugateQ;

		Vector3 ret(w.GetX(), w.GetY(), w.GetZ());

		return ret;
	}

	Vector3 Vector3::Rotate(const Quaternion& rotation) const
	{
		Quaternion conjugateQ = rotation.Conjugate();
		Quaternion w = rotation * (*this) * conjugateQ;

		Vector3 ret(w.GetX(), w.GetY(), w.GetZ());

		return ret;
	}

	Vector3 Vector3::Normalized() const
	{
		return *this / Length();
	}

	Vector3 Vector3::Lerp(const Vector3& r, float lerpFactor) const
	{
		return (r - *this) * lerpFactor + *this;
	}

	// R = L - 2 (L.dot(n)n)
	// normal 必须为单位向量
	Vector3 Vector3::Reflect(const Vector3& normal) const
	{
		return *this - (normal * (this->Dot(normal) * 2));
	}

	Vector3 Vector3::operator+(const Vector3& r) const
	{
		Vector3 result;
		for (unsigned int i = 0; i < 3; i++)
		{
			result[i] = m_Values[i] + r[i];
		}

		return result;
	}

	Vector3 Vector3::operator-(const Vector3& r) const
	{
		Vector3 result;
		for (unsigned int i = 0; i < 3; i++)
		{
			result[i] = m_Values[i] - r[i];
		}

		return result;
	}

	Vector3 Vector3::operator*(const float& r) const
	{
		Vector3 result;
		for (unsigned int i = 0; i < 3; i++)
		{
			result[i] = m_Values[i] * r;
		}

		return result;
	}

	Vector3 Vector3::operator/(const float& r) const
	{
		Vector3 result;
		for (unsigned int i = 0; i < 3; i++)
		{
			result[i] = m_Values[i] / r;
		}

		return result;
	}

	Vector3& Vector3::operator/=(const float& r)
	{
		for (unsigned int i = 0; i < 3; i++)
		{
			(*this)[i] = m_Values[i] / r;
		}

		return *this;
	}

	bool Vector3::operator!=(const Vector3& r) const
	{
		return !operator==(r);
	}

	bool Vector3::operator==(const Vector3& r) const
	{
		for (unsigned int i = 0; i < 3; i++)
		{
			if ((*this)[i] != r[i])
			{
				return false;
			}
		}
		return true;
	}

	Vector3& Vector3::operator*=(const float& r)
	{
		for (unsigned int i = 0; i < 3; i++)
		{
			(*this)[i] = m_Values[i] * r;
		}

		return *this;
	}

	Vector3& Vector3::operator-=(const Vector3& r)
	{
		for (unsigned int i = 0; i < 3; i++)
		{
			(*this)[i] = m_Values[i] - r[i];
		}

		return *this;
	}

	Vector3& Vector3::operator+=(const Vector3& r)
	{
		for (unsigned int i = 0; i < 3; i++)
		{
			(*this)[i] = m_Values[i] + r[i];
		}

		return *this;
	}

	std::ostream& operator<<(std::ostream& stream, const Vector3& vector)
	{
		stream << "Vector3(" << vector.GetX() << "," << vector.GetY() << "," << vector.GetZ() << ")";
		return stream;
	}
}