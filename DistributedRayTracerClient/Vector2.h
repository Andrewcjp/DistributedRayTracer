#pragma once
#include <math.h>
class Vector2
{
private:
	float	m_element[2];

public:
	Vector2();

	Vector2(const Vector2& rhs);

	Vector2(float x, float y);

	~Vector2() { ; }

	float operator [] (const int i) const;
	float& operator [] (const int i);
	Vector2 operator + (const Vector2& rhs) const;
	Vector2 operator - (const Vector2& rhs) const;
	Vector2& operator = (const Vector2& rhs);
	Vector2 operator * (const Vector2& rhs) const;
	Vector2 operator * (float scale) const;
	Vector2 operator /(float amt) const;
	float Norm()	const;
	float Norm_Sqr() const;
	Vector2 Normalise();

	float DotProduct(const Vector2& rhs) const;
	Vector2 CrossProduct(const Vector2& rhs) const;

	Vector2 Reflect(const Vector2& n) const;
	Vector2 Refract(const Vector2& n, float r_index) const;

	void SetZero();

	inline void SetVector(float x, float y)
	{
		m_element[0] = x; m_element[1] = y;
	}
};

