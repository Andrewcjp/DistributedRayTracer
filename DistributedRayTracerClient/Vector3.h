/*---------------------------------------------------------------------
*
* Copyright © 2015  Minsi Chen
* E-mail: m.chen@derby.ac.uk
*
* The source is written for the Graphics I and II modules. You are free
* to use and extend the functionality. The code provided here is functional
* however the author does not guarantee its performance.
---------------------------------------------------------------------*/
#pragma once
class Vector3
{
private:
	float	m_element[3];

public:
	Vector3();

	Vector3(const Vector3& rhs);

	Vector3(float x, float y, float z);

	~Vector3() { ; }

	float operator [] (const int i) const;
	float& operator [] (const int i);
	Vector3 operator + (const Vector3& rhs) const;
	Vector3 operator - (const Vector3& rhs) const;
	Vector3& operator = (const Vector3& rhs);
	Vector3 operator * (const Vector3& rhs) const;
	Vector3 operator * (float scale) const;
	Vector3 operator /(float amt) const;
	float Norm()	const;
	float Norm_Sqr() const;
	Vector3 Normalise();
	float x() {
		return m_element[0];
	}
	float DotProduct(const Vector3& rhs) const;
	Vector3 CrossProduct(const Vector3& rhs) const;

	Vector3 Reflect(const Vector3& n) const;
	Vector3 Refract(const Vector3& n, float r_index) const;

	void SetZero();

	inline void SetVector(float x, float y, float z)
	{
		m_element[0] = x; m_element[1] = y; m_element[2] = z;
	}
};
