#pragma once
#include <vector>
#include <iostream>
#include "Vector3.h"
#include "Vector2.h"
#include "Triangle.h"
#include "Mesh.h"
class ObjLoader
{
public:
	ObjLoader(Vector3 offset) {
		toffset = offset;
	}
	~ObjLoader();
	Mesh* BuildMesh(const char * path);
	
	bool ObjLoader::Load(const char * path,
		std::vector<Vector3> & out_vertices,
		std::vector<Vector3> & out_uvs,
		std::vector<Vector3> & out_normals);
	float xmax = 0;
	float xmin = 0;
private:
	

	Vector3 toffset;
	std::vector<Triangle*> tris;

};

