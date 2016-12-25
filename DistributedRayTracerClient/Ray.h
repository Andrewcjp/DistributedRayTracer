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

#include "Vector3.h"
#include "Vector3d.h"
#include "Ray.h"
#define FARFAR_AWAY  1000000.0			//let's hope this is reasonably large ;)
//A basic struct for recording a ray hit result
struct RayHitResult
{
	Vector3d	normal;			// the surface normal at the intersection ( e.g. useful for lighting);
	Vector3d point;			// the exact position of the intersection point
	double t;				//the parametric value of the resulting intersections
	void* data;				//a pointer to misc. data, e.g. this could be material data for calculating lighting; or the hit object itself
	float CurrentMedium;
};


class Ray
{

	private:
		Vector3d				m_start;   //origin of the ray
		Vector3d				m_ray;     //direct of the ray, this must be a unit vector

	public:
			static RayHitResult		s_defaultHitResult; //This is a constant for storing the default ray intersection result, i.e. nothing
			Ray();
			~Ray();

			inline void SetRay(Vector3 start, Vector3 ray)
			{
				m_start = start;
				m_ray = ray;
			}

			inline Vector3d& GetRay()
			{
				return m_ray;
			}

			inline Vector3d& GetRayStart()
			{
				return m_start;
			}
};

