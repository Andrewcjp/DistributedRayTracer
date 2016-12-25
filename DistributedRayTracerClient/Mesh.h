#pragma once
#include <vector>
#include "Vector3.h"
#include "Triangle.h"
class Mesh : public Primitive {
public:
	Mesh(std::vector<Triangle*> tris) {
		m_Data = tris;
	}

	RayHitResult IntersectByRay(Ray& ray);
	std::vector<Triangle*> m_Data;
private:
	
};

