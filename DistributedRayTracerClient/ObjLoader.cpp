#include "ObjLoader.h"
//#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>

ObjLoader::~ObjLoader()
{
}

Mesh* ObjLoader::BuildMesh(const char * path)
{
	std::vector<Vector3>  out_vertices;
	std::vector<Vector3>  out_uvs;
	std::vector<Vector3>  out_normals;
	Load(path, out_vertices, out_uvs, out_normals);

	for (unsigned int i = 0; i < out_vertices.size(); i += 3) {
		
		Triangle* newtris = new Triangle(toffset + out_vertices[i], toffset + out_vertices[i + 1], toffset + out_vertices[i + 2]);
		newtris->SetNormals(out_normals[i], out_normals[i + 1], out_normals[i + 2]);
		newtris->SetTexCoords(out_uvs[i], out_uvs[i + 1], out_uvs[i + 2]);
		tris.push_back(newtris);
	}
	return new Mesh(tris);
}


bool ObjLoader::Load(const char * path,
	std::vector<Vector3> & out_vertices,
	std::vector<Vector3> & out_uvs,
	std::vector<Vector3> & out_normals)
{

	printf("Loading OBJ file %s...\n", path);

	std::vector<unsigned int> vertIndices;
	std::vector<unsigned int> uvIndices;
	std::vector<unsigned int> normalIndices;
	std::vector<Vector3> verts;
	std::vector<Vector3> uvs;
	std::vector<Vector3> normals;
	FILE * file;
	errno_t err = fopen_s(&file, path, "r");
	if (err != 0) {
		printf("Failed to Open File\n");
		return false;
	}
	//dangerous but effective!
	while (true) {
		char line[128];
		int res = fscanf(file, "%s", line);
		if (res == EOF) {
			break;
		}
		if (strcmp(line, "v") == 0) {
			//we have encoutered a v value which contains a vertex position vector.
			float x, y, z = 0;
			fscanf(file, "%f %f %f\n", &x, &y, &z);
			Vector3 vertex(x, y, z);
			verts.push_back(vertex);
		}
		else if (strcmp(line, "vt") == 0) {
			//we have encoutered a vt value containg uv value for diffrant image formats this might need to be changed
			float x, y = 0;
			fscanf(file, "%f %f\n", &x, &y);
			Vector3 uv(x, y, 0);
			uvs.push_back(uv);
		}
		else if (strcmp(line, "vn") == 0) {
			//we have encoutered a vn value that is normal information
			float x, y, z = 0;
			fscanf(file, "%f %f %f\n", &x, &y, &z);
			Vector3 normal(x, y, z);
			normals.push_back(normal);
		}
		else if (strcmp(line, "f") == 0) {
			//we have encoutered a f value which contain index information
			std::string vertex1;
			std::string vertex2;
			std::string vertex3;
			unsigned int vertIndex[3];
			unsigned int uvIndex[3];
			unsigned int normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertIndex[0], &uvIndex[0], &normalIndex[0], &vertIndex[1], &uvIndex[1], &normalIndex[1], &vertIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File Read Error\n");
				fclose(file);
				return false;
			}
			vertIndices.push_back(vertIndex[0]);
			vertIndices.push_back(vertIndex[1]);
			vertIndices.push_back(vertIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else {
			//extra un parseable information is present so remove it!
			char dumpbuffer[1000];
			fgets(dumpbuffer, 1000, file);
		}

	}
	for (unsigned int i = 0; i < vertIndices.size(); i++) {


		unsigned int vertIndex = vertIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];
		//get the -1 information
		Vector3 vertex = verts[vertIndex - 1];
		Vector3 uv = uvs[uvIndex - 1];
		Vector3 normal = normals[normalIndex - 1];

		if (xmin > vertex[0]) {
			xmin = vertex[0];
		}
		if (xmax < vertex[0]) {
			xmax = vertex[0];
		}
		//push back to our vectors
		out_vertices.push_back(vertex);
		out_uvs.push_back(uv);
		out_normals.push_back(normal);

	}
	fclose(file);//close that file!
	return true;
}


