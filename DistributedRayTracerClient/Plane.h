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
#include "Primitive.h"
#include "Vector3.h"
#include "Ray.h"

class Plane : public Primitive
{
	private:
		Vector3			m_normal;			//normal to the plane
		double			m_offset;			//position of the plane along the normal
		Vector3 UAxis; 
		Vector3 VAxis;
		bool m_haspattern = false;
	public:
						Plane();
						~Plane();

		RayHitResult	IntersectByRay(Ray& ray);
		inline void SetPattern(bool state) {
			m_haspattern = state;
		}
		void SetPlane(const Vector3 & normal, double offset, bool pattern = false);
		Colour GetDiffuseColour(Vector3 point);
		Colour GetNormalColour(Vector3 point);
		inline Vector3 GetUAxis() {
			return UAxis;
		}
		inline Vector3 GetVAxis() {
			return VAxis;
		}
};

