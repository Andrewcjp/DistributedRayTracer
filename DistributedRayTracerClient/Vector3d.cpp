#include "Vector3d.h"

Vector3d::Vector3d()
{
	m_element[0] = 0.0;
	m_element[1] = 0.0;
	m_element[2] = 0.0;
}

Vector3d::Vector3d(const Vector3d& rhs)
{
	m_element[0] = rhs[0];
	m_element[1] = rhs[1];
	m_element[2] = rhs[2];
}

Vector3d::Vector3d(const Vector3 & rhs)
{
	m_element[0] = rhs[0];
	m_element[1] = rhs[1];
	m_element[2] = rhs[2];
}
Vector3d::Vector3d(Vector3 & rhs)
{
	m_element[0] = rhs[0];
	m_element[1] = rhs[1];
	m_element[2] = rhs[2];
}
Vector3d::Vector3d(double x, double y, double z)
{
	m_element[0] = x; m_element[1] = y; m_element[2] = z;
}

Vector3d::operator Vector3() const
{
	return Vector3(m_element[0], m_element[1], m_element[2]);
}

Vector3d::operator Vector3()
{
	return Vector3(m_element[0], m_element[1], m_element[2]);
}

double Vector3d::operator [] (const int i) const
{
	return m_element[i];
}

double& Vector3d::operator [] (const int i)
{
	return m_element[i];
}

Vector3d Vector3d::operator + (const Vector3d& rhs) const
{
	return Vector3d(
		(*this)[0] + rhs[0],
		(*this)[1] + rhs[1],
		(*this)[2] + rhs[2]);
}

Vector3d Vector3d::operator - (const Vector3d& rhs) const
{
	return Vector3d(
		(*this)[0] - rhs[0],
		(*this)[1] - rhs[1],
		(*this)[2] - rhs[2]);
}

Vector3d& Vector3d::operator = (const Vector3d& rhs)
{
	m_element[0] = rhs[0];
	m_element[1] = rhs[1];
	m_element[2] = rhs[2];
	return *this;
}

Vector3d Vector3d::operator * (const Vector3d& rhs) const
{
	return Vector3d(
		m_element[0] * rhs[0],
		m_element[1] * rhs[1],
		m_element[2] * rhs[2]);
}

Vector3d Vector3d::operator * (double scale) const
{
	return Vector3d(
		m_element[0] * scale,
		m_element[1] * scale,
		m_element[2] * scale
	);
}

Vector3d & Vector3d::operator=(const Vector3 & rhs)
{
	m_element[0] = rhs[0];
	m_element[1] = rhs[1];
	m_element[2] = rhs[2];
	return *this;
}

double Vector3d::Norm() const
{
	return sqrt(m_element[0] * m_element[0] + m_element[1] * m_element[1] + m_element[2] * m_element[2]);
}

double Vector3d::Norm_Sqr() const
{
	return m_element[0] * m_element[0] + m_element[1] * m_element[1] + m_element[2] * m_element[2];
}

double Vector3d::DotProduct(const Vector3d& rhs) const
{
	return m_element[0] * rhs[0] + m_element[1] * rhs[1] + m_element[2] * rhs[2];
}

Vector3d Vector3d::Normalise()
{
	double length = this->Norm();

	if (length > 1.0e-16)
	{
		double invLen = 1.0 / length;

		m_element[0] *= invLen;
		m_element[1] *= invLen;
		m_element[2] *= invLen;
	}

	return *this;
}

Vector3d Vector3d::CrossProduct(const Vector3d& rhs) const
{
	return Vector3d(
		(m_element[1] * rhs[2] - m_element[2] * rhs[1]),
		(m_element[2] * rhs[0] - m_element[0] * rhs[2]),
		(m_element[0] * rhs[1] - m_element[1] * rhs[0])
	);
}

Vector3d Vector3d::Reflect(const Vector3d & n) const
{
	Vector3d result;

	double IndotN = -2.0*this->DotProduct(n);

	result = *this + n*IndotN;

	return result;
}

Vector3d Vector3d::Refract(const Vector3d & n, double r_index) const
{
	Vector3d result;
	result.SetZero();
	double IndotN = this->DotProduct(n);

	if (IndotN > 0.0)
	{
		Vector3d nn = n*(-1.0);
		IndotN = -this->DotProduct(nn);
	}
	else
		IndotN = -IndotN;

	double k = 1.0 - r_index*r_index*(1.0 - IndotN*IndotN);

	if (k >= 0.0)
		result = (*this)*r_index + n*(r_index*IndotN - sqrt(k));

	return result;
}

void Vector3d::SetZero()
{
	m_element[0] = m_element[1] = m_element[2] = 0.0;
}
