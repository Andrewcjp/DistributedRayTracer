/*---------------------------------------------------------------------
*
* Copyright © 2015  Minsi Chen
* E-mail: m.chen@derby.ac.uk
*
* The source is written for the Graphics I and II modules. You are free
* to use and extend the functionality. The code provided here is functional
* however the author does not guarantee its performance.
---------------------------------------------------------------------*/
#include <math.h>
#include "Sphere.h"

Sphere::Sphere()
{
	//the default sphere is centred around the origin of the world coordinate
	//default radius is 2.0

	m_centre.SetZero();
	m_radius = 2.0;
	m_primtype = PRIMTYPE_Sphere;
	m_Vn = Vector3(0, 1, 0);
	m_Ve = Vector3(1, 0, 0);
	m_Vc = m_Vn.CrossProduct(m_Ve);
}

Sphere::Sphere(double x, double y, double z, double r)
{
	m_centre.SetVector(x, y, z);
	m_radius = r;
	m_primtype = PRIMTYPE_Sphere;
	m_Vn = Vector3(0, 1, 0);
	m_Ve = Vector3(1, 0, 0);
	m_Vc = m_Vn.CrossProduct(m_Ve);
}

Sphere::~Sphere()
{
}

RayHitResult Sphere::IntersectByRay(Ray& ray)
{
	RayHitResult result = Ray::s_defaultHitResult;

	Vector3 negateRay = ray.GetRay();

	negateRay[0] = -ray.GetRay()[0];
	negateRay[1] = -ray.GetRay()[1];
	negateRay[2] = -ray.GetRay()[2];

	Vector3 centreToEye = ray.GetRayStart() - this->GetCentre();

	double dotRayCentreToEye = ray.GetRay().DotProduct(centreToEye);
	double dotRayRay = ray.GetRay().DotProduct(ray.GetRay());
	double dotCentreToEye = centreToEye.DotProduct(centreToEye);
	double radiusSqr = m_radius*m_radius;

	double discriminant = pow(2.0*dotRayRay*dotRayCentreToEye, 2) - 4.0*dotRayRay*(dotRayCentreToEye - radiusSqr);

	if (discriminant < 0.0) return result;

	double omega_plus = negateRay.DotProduct(centreToEye) +
		sqrt(dotRayCentreToEye*dotRayCentreToEye - dotRayRay*(dotCentreToEye - radiusSqr));
	omega_plus /= dotRayRay;

	double omega_minus = negateRay.DotProduct(centreToEye) -
		sqrt(dotRayCentreToEye*dotRayCentreToEye - dotRayRay*(dotCentreToEye - radiusSqr));

	omega_minus /= dotRayRay;

	result.t = omega_plus < omega_minus ? omega_plus : omega_minus;
	result.data = this;

	Vector3 intersection_point = ray.GetRayStart() + ray.GetRay()*result.t;
	result.point = intersection_point;
	result.normal = (intersection_point - m_centre).Normalise();

	return result;
}
#define PI 3.14159
Colour Sphere::GetDiffuseColour(Vector3 point) {
	if (GetMaterial()->HasDiffuseTexture()) {
		float vscale = 1;
		float uscale = 1;
		Vector3 vp = (point - m_centre) * m_radius;
		float phi = acosf(-vp.DotProduct(m_Vn));
		float u, v = phi * vscale * (1.0f / PI);
		float theta = (acosf(m_Ve.DotProduct(vp)) / sinf(phi)) * (2.0f / PI);
		if (m_Vc.DotProduct(vp) >= 0) {
			u = (1.0f - theta) *uscale;
		}
		else {
			u = theta * uscale;
		}
		return GetMaterial()->GetDiffuseTexture()->GetTexelColour(u, v);// *GetMaterial()->GetDiffuseColour();
	}
	return GetMaterial()->GetDiffuseColour();

}