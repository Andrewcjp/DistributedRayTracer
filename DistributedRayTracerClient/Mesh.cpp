#include "Mesh.h"



RayHitResult Mesh::IntersectByRay(Ray & ray)
{
	/*for (int i = 0; i < m_Data.size(); i++) {
		RayHitResult result = m_Data[i].IntersectByRay(ray);
		if (result.data) {
			return result;
		}
	}*/
	return RayHitResult();
}
