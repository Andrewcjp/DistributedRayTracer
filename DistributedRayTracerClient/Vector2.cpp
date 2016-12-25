#include "Vector2.h"
Vector2::Vector2()
{
	m_element[0] = 0.0f;
	m_element[1] = 0.0f;
}

Vector2::Vector2(const Vector2& rhs)
{
	m_element[0] = rhs[0];
	m_element[1] = rhs[1];
}

Vector2::Vector2(float x, float y)
{
	m_element[0] = x; m_element[1] = y;
}

float Vector2::operator [] (const int i) const
{
	return m_element[i];
}

float& Vector2::operator [] (const int i)
{
	return m_element[i];
}

Vector2 Vector2::operator + (const Vector2& rhs) const
{
	return Vector2(
		(*this)[0] + rhs[0],
		(*this)[1] + rhs[1]);
}

Vector2 Vector2::operator - (const Vector2& rhs) const
{
	return Vector2(
		(*this)[0] - rhs[0],
		(*this)[1] - rhs[1]);
}

Vector2& Vector2::operator = (const Vector2& rhs)
{
	m_element[0] = rhs[0];
	m_element[1] = rhs[1];

	return *this;
}

Vector2 Vector2::operator * (const Vector2& rhs) const
{
	return Vector2(
		m_element[0] * rhs[0],
		m_element[1] * rhs[1]);
}

Vector2 Vector2::operator * (float scale) const
{
	return Vector2(
		m_element[0] * scale,
		m_element[1] * scale
	);
}

Vector2 Vector2::operator/(float amt) const
{
	return Vector2(
		m_element[0] / amt,
		m_element[1] / amt
	);
}

float Vector2::Norm() const
{
	return sqrt(m_element[0] * m_element[0] + m_element[1] * m_element[1] );
}

float Vector2::Norm_Sqr() const
{
	return m_element[0] * m_element[0] + m_element[1] * m_element[1] ;
}

float Vector2::DotProduct(const Vector2& rhs) const
{
	return m_element[0] * rhs[0] + m_element[1] * rhs[1];
}

Vector2 Vector2::Normalise()
{
	float length = this->Norm();

	if (length > 1.0e-8f)
	{
		float invLen = 1.0f / length;

		m_element[0] *= invLen;
		m_element[1] *= invLen;

	}

	return *this;
}

Vector2 Vector2::CrossProduct(const Vector2& rhs) const
{
	/*return Vector2(
		(m_element[1] * rhs[2] - m_element[2] * rhs[1]),
		(m_element[2] * rhs[0] - m_element[0] * rhs[2])
	);*/
	return Vector2();
}

Vector2 Vector2::Reflect(const Vector2 & n) const
{
	Vector2 result;

	float IndotN = -2.0*this->DotProduct(n);

	result = *this + n*IndotN;

	return result;
}

Vector2 Vector2::Refract(const Vector2 & n, float r_index) const
{
	Vector2 result;
	result.SetZero();
	float IndotN = this->DotProduct(n);

	if (IndotN > 0.0)
	{
		Vector2 nn = n*(-1.0);
		IndotN = -this->DotProduct(nn);
	}
	else
		IndotN = -IndotN;

	float k = 1.0 - r_index*r_index*(1.0 - IndotN*IndotN);

	if (k >= 0.0)
		result = (*this)*r_index + n*(r_index*IndotN - sqrt(k));

	return result;
}

void Vector2::SetZero()
{
	m_element[0] = m_element[1] = 0.0f;
}
