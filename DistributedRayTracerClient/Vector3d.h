#include <math.h>
#include "Vector3.h"
#pragma once
class Vector3d
{
private:
	double	m_element[3];

public:
	Vector3d();

	Vector3d(const Vector3d& rhs);
	Vector3d(const Vector3& rhs);
	Vector3d(Vector3& rhs);
	Vector3d(double x, double y, double z);
	operator Vector3() const;
	operator Vector3();
	//Vector3(const Vector3d& rhs);
	~Vector3d() { ; }

	double operator [] (const int i) const;
	double& operator [] (const int i);
	Vector3d operator + (const Vector3d& rhs) const;
	Vector3d operator - (const Vector3d& rhs) const;
	Vector3d& operator = (const Vector3d& rhs);
	Vector3d operator * (const Vector3d& rhs) const;
	Vector3d operator * (double scale) const;
	Vector3d& operator = (const Vector3& rhs);
	double Norm()	const;
	double Norm_Sqr() const;
	Vector3d Normalise();

	double DotProduct(const Vector3d& rhs) const;
	Vector3d CrossProduct(const Vector3d& rhs) const;

	Vector3d Reflect(const Vector3d& n) const;
	Vector3d Refract(const Vector3d& n, double r_index) const;

	void SetZero();

	inline void SetVector(double x, double y, double z)
	{
		m_element[0] = x; m_element[1] = y; m_element[2] = z;
	}
};

