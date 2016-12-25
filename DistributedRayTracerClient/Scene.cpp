
#include "Scene.h"
#include "Sphere.h"
#include "Plane.h"
#include "Box.h"
#include "ObjLoader.h"


Scene::Scene()
{

}


Scene::~Scene()
{
	CleanupScene();
}

void Scene::InitDefaultScene()
{
	//Create a box and its material
	Primitive* newobj = new Box(Vector3(-4.0, 4.0, -20.0), 10.0, 15.0, 4.0);
	Material* newmat = new Material();
	//mat for the box1
	newmat->SetAmbientColour(0.0, 0.0, 0.0);
	newmat->SetDiffuseColour(1.0, 0.0, 0.0);
	newmat->SetSpecularColour(1.0, 1.0, 1.0);
	newmat->SetReflectivity(1);
	newmat->SetRefractivity(1.1);
	newmat->SetSpecPower(20);
	newobj->SetMaterial(newmat);
	m_sceneObjects.push_back(newobj);
	m_objectMaterials.push_back(newmat);

	newobj = new Box(Vector3(4.0, 4.0, -15.0), 4.0, 20.0, 4.0);
	newmat = new Material();
	//mat for the box2
	newmat->SetAmbientColour(0.0, 0.0, 0.0);
	newmat->SetDiffuseColour(0.8, 0.8, 0.8);
	newmat->SetSpecularColour(1.0, 1.0, 1.0);
	newmat->SetReflectivity(1);
	newmat->SetRefractivity(1.1);
	newmat->SetSpecPower(20);
	newobj->SetMaterial(newmat);
	m_sceneObjects.push_back(newobj);
	m_objectMaterials.push_back(newmat);
	//todo: remove
	newobj = new Box(Vector3(10.0, 4.0, -15.0), 4.0, 4.0, 4.0);
	newmat = new Material();
	//mat for the box2
	newmat->SetAmbientColour(0.0, 0.0, 0.0);
	newmat->SetDiffuseColour(1, 1, 1);
	newmat->SetSpecularColour(0.0, 0.0, 0.0);
	newmat->SetReflectivity(1);
	newmat->SetRefractivity(0);
	//Texture* spDiffuse = new Texture();
	//spDiffuse->LoadTextureFromFile("../newBricks.bmp");
	//newmat->SetDiffuseTexture(spDiffuse);
	newmat->SetSpecPower(20);
	newobj->SetMaterial(newmat);
	m_sceneObjects.push_back(newobj);
	m_objectMaterials.push_back(newmat);

	newobj = new Plane();
	static_cast<Plane*>(newobj)->SetPlane(Vector3(0.0, 0, 1), -20);
	newmat = new Material();
	//mat for the box2
	newmat->SetAmbientColour(0.0, 0.0, 0.0);
	newmat->SetDiffuseColour(1, 1, 1);
	newmat->SetSpecularColour(0.0, 0.0, 0.0);
	/*Texture* Diffuse = new Texture();
	Diffuse->LoadTextureFromFile("../newBricks.bmp");
	newmat->SetDiffuseTexture(Diffuse);
	Texture* normal = new Texture();
	normal->LoadTextureFromFile("../N_newBricks.bmp");*/
//	newmat->SetNormalTexture(normal);
	newmat->SetSpecPower(10);
	newobj->SetMaterial(newmat);
	m_sceneObjects.push_back(newobj);
	m_objectMaterials.push_back(newmat);
//	m_Textures.push_back(Diffuse);
	//Create sphere 1 and its material
	newobj = new Sphere(3.0, 2, -3.5, 2.0); //sphere 2
	newmat = new Material();
	newmat->SetAmbientColour(0.0, 0.0, 0.0);
	newmat->SetDiffuseColour(0.0, 0.8, 0.0);
	newmat->SetSpecularColour(1.0, 1.0, 1.0);
	newmat->SetReflectivity(1);
	newmat->SetRefractivity(1.1);
	newmat->SetSpecPower(2);
	newobj->SetMaterial(newmat);
	m_sceneObjects.push_back(newobj);
	m_objectMaterials.push_back(newmat);

	//Create sphere 4 and its material
	newobj = new Sphere(-10.0, 2, -3.5, 2.0); //sphere 2
	newmat = new Material();
	newmat->SetAmbientColour(0.0, 0.0, 0.0);
	newmat->SetDiffuseColour(1.0, 1.0, 1.0);
	newmat->SetSpecularColour(1.0, 1.0, 1.0);
	newmat->SetReflectivity(1);
	newmat->SetSpecPower(2);
	newobj->SetMaterial(newmat);
	m_sceneObjects.push_back(newobj);
	m_objectMaterials.push_back(newmat);

	//Create sphere 2 and its material
	newobj = new Sphere(-2.0, 3.0, -5.0, 3.0); //sphere 3
	newmat = new Material();
	newmat->SetAmbientColour(0.0, 0.0, 0.0);
	newmat->SetDiffuseColour(0.0, 0.0, 0.9);
	newmat->SetSpecularColour(1.0, 1.0, 1.0);
	newmat->SetReflectivity(1);
	newmat->SetRefractivity(1);
	newmat->SetSpecPower(20);
	newobj->SetMaterial(newmat);
	m_sceneObjects.push_back(newobj);
	m_objectMaterials.push_back(newmat);


	newobj = new Plane(); //an xz plane at the origin, floor
	static_cast<Plane*>(newobj)->SetPlane(Vector3(0.0, 1.0, 0.0), 0.0, true);
	newmat = new Material();
	newmat->SetAmbientColour(0.0, 0.0, 0.0);
	newmat->SetDiffuseColour(1.0, 0.0, 0.0);
	newmat->SetSpecularColour(0.0, 0.0, 0.0);
	newmat->SetSpecPower(10);
	newmat->SetCastShadow(false);
	newobj->SetMaterial(newmat);
	m_sceneObjects.push_back(newobj);
	m_objectMaterials.push_back(newmat);

	newobj = new Plane(); //an xz plane 40 units above, ceiling
	static_cast<Plane*>(newobj)->SetPlane(Vector3(0.0, -1.0, 0.0), -40.0, true);
	newobj->SetMaterial(newmat);
	m_sceneObjects.push_back(newobj);


	newmat = new Material();
	newmat->SetAmbientColour(0.0, 0.0, 0.0);
	newmat->SetDiffuseColour(0.0, 1.0, 0.0);
	newmat->SetSpecularColour(0.0, 0.0, 0.0);
	newmat->SetSpecPower(10);
	newmat->SetCastShadow(false);
	newobj->SetMaterial(newmat);

	newobj = new Plane(); //an xy plane 40 units along -z axis, 
	static_cast<Plane*>(newobj)->SetPlane(Vector3(0.0, 0.0, 1.0), -40.0, true);
	m_sceneObjects.push_back(newobj);
	newobj->SetMaterial(newmat);
	//m_objectMaterials.push_back(newmat);

	newobj = new Plane(); //an xy plane 40 units along the z axis
	static_cast<Plane*>(newobj)->SetPlane(Vector3(0.0, 0.0, -1.0), -40.0, true);
	newobj->SetMaterial(newmat);
	m_sceneObjects.push_back(newobj);

	newobj = new Plane(); //an yz plane 20 units along -x axis
	static_cast<Plane*>(newobj)->SetPlane(Vector3(1.0, 0.0, 0.0), -20.0, true);
	newmat = new Material();
	newmat->SetAmbientColour(0.0, 0.0, 0.0);
	newmat->SetDiffuseColour(0.0, 0.0, 1.0);
	newmat->SetSpecularColour(0.0, 0.0, 0.0);
	newmat->SetSpecPower(10);
	newmat->SetCastShadow(false);
	newobj->SetMaterial(newmat);
	m_sceneObjects.push_back(newobj);
	m_objectMaterials.push_back(newmat);

	newobj = new Plane(); //an yz plane 20 units along +x axis
	static_cast<Plane*>(newobj)->SetPlane(Vector3(-1.0, 0.0, 0.0), -20.0, true);
	newobj->SetMaterial(newmat);
	m_sceneObjects.push_back(newobj);

	//Vector3 position(7, 5, 0);
	//ObjLoader loader(position);
	//newobj = new Box(position, 2, 4, 4);
	//newobj->OverridePrimType(Primitive::PRIMTYPE_Bounding);
	//m_sceneObjects.push_back(newobj);
	////todo: rotation?
	//Mesh* mesh = loader.BuildMesh("../Monkey.obj");
	//for (int i = 0; i < mesh->m_Data.size(); i++) {
	//	newobj = mesh->m_Data[i];
	//	newmat = new Material();
	//	//mat for the box2
	//	newmat->SetAmbientColour(0.0, 0.0, 0.0);
	//	newmat->SetDiffuseColour(1.0, 1.0, 1.0);
	//	newmat->SetSpecularColour(0.0, 0.0, 0.0);
	//	newmat->SetReflectivity(0);
	//	newmat->SetRefractivity(0);
	//	newmat->SetSpecPower(10);
	//	Texture* testDiffuse = new Texture();
	//	testDiffuse->LoadTextureFromFile("../newBricks.bmp");
	//	newmat->SetDiffuseTexture(testDiffuse);
	//	newobj->SetMaterial(newmat);
	//	m_sceneObjects.push_back(newobj);
	//	m_objectMaterials.push_back(newmat);
	//}
	Light *newlight = new Light();
	newlight->SetLightPosition(0, 5, 10.0);
	newlight->SetLightColour(0.5, 0.5, 0.5);
	//m_lights.push_back(newlight);
		//Create one light source for the scene
	newlight = new Light();
	newlight->SetLightPosition(0.0, 15.0, 10.0);
	m_lights.push_back(newlight);

	//A black background
	m_background.SetVector(0, 0, 0);

	//default scene width and height;
	m_sceneWidth = 1.33333333;
	m_sceneHeight = 1.0;

	//default camera position and look at
	m_activeCamera.SetPositionAndLookAt(Vector3(0.0, 10.0, 13.0), Vector3(0.0, 7, 0));
}

void Scene::CleanupScene()
{
	//Cleanup object list
	std::vector<Primitive*>::iterator prim_iter = m_sceneObjects.begin();

	while (prim_iter != m_sceneObjects.end())
	{
		delete *prim_iter;
		prim_iter++;
	}

	m_sceneObjects.clear();

	//Cleanup material list
	std::vector<Material*>::iterator mat_iter = m_objectMaterials.begin();

	while (mat_iter != m_objectMaterials.end())
	{
		delete *mat_iter;
		mat_iter++;
	}
	m_objectMaterials.clear();

	//cleanup light list
	std::vector<Light*>::iterator lit_iter = m_lights.begin();

	while (lit_iter != m_lights.end())
	{
		delete *lit_iter;
		lit_iter++;
	}

	m_lights.clear();
}

void Scene::InitVillage()
{
	//Create a box and its material
	Primitive* newobj = new Box(Vector3(-4.0, 4.0, -20.0), 10.0, 15.0, 4.0);
	Material* newmat = new Material();
	//mat for the box1
	//newmat->SetAmbientColour(0.0, 0.0, 0.0);
	//newmat->SetDiffuseColour(1.0, 0.0, 0.0);
	//newmat->SetSpecularColour(1.0, 1.0, 1.0);
	//newmat->SetReflectivity(1);
	//newmat->SetRefractivity(1.1);
	//newmat->SetSpecPower(20);
	//newobj->SetMaterial(newmat);
	//m_sceneObjects.push_back(newobj);
	//m_objectMaterials.push_back(newmat);

	//newobj = new Box(Vector3(4.0, 4.0, -15.0), 4.0, 20.0, 4.0);
	//newmat = new Material();
	////mat for the box2
	//newmat->SetAmbientColour(0.0, 0.0, 0.0);
	//newmat->SetDiffuseColour(0.8, 0.8, 0.8);
	//newmat->SetSpecularColour(1.0, 1.0, 1.0);
	//newmat->SetReflectivity(1);
	//newmat->SetRefractivity(1.1);
	//newmat->SetSpecPower(20);
	//newobj->SetMaterial(newmat);
	//m_sceneObjects.push_back(newobj);
	//m_objectMaterials.push_back(newmat);
	////todo: remove
	//newobj = new Box(Vector3(10.0, 4.0, -15.0), 4.0, 4.0, 4.0);
	//newmat = new Material();
	////mat for the box2
	//newmat->SetAmbientColour(0.0, 0.0, 0.0);
	//newmat->SetDiffuseColour(1, 1, 1);
	//newmat->SetSpecularColour(0.0, 0.0, 0.0);
	//newmat->SetReflectivity(1);
	//newmat->SetRefractivity(0);
	////Texture* spDiffuse = new Texture();
	////spDiffuse->LoadTextureFromFile("../newBricks.bmp");
	////newmat->SetDiffuseTexture(spDiffuse);
	//newmat->SetSpecPower(20);
	//newobj->SetMaterial(newmat);
	//m_sceneObjects.push_back(newobj);
	//m_objectMaterials.push_back(newmat);

	//newobj = new Plane();
	//static_cast<Plane*>(newobj)->SetPlane(Vector3(0.0, 0, 1), -20);
	//newmat = new Material();
	////mat for the box2
	//newmat->SetAmbientColour(0.0, 0.0, 0.0);
	//newmat->SetDiffuseColour(1, 1, 1);
	//newmat->SetSpecularColour(0.0, 0.0, 0.0);
	////Texture* Diffuse = new Texture();
	////Diffuse->LoadTextureFromFile("../sky.bmp");
	////newmat->SetDiffuseTexture(Diffuse);
	//////Texture* normal = new Texture();
	////normal->LoadTextureFromFile("../N_newBricks.bmp");
	////newmat->SetNormalTexture(normal);
	//newmat->SetSpecPower(10);
	//newobj->SetMaterial(newmat);
	//m_sceneObjects.push_back(newobj);
	//m_objectMaterials.push_back(newmat);
	//m_Textures.push_back(Diffuse);
	//Create sphere 1 and its material

	//newobj = new Plane(); //an xz plane at the origin, floor
	//static_cast<Plane*>(newobj)->SetPlane(Vector3(0.0, 1.0, 0.0), 0.0, true);
	//newmat = new Material();
	//newmat->SetAmbientColour(0.0, 0.0, 0.0);
	//newmat->SetDiffuseColour(1.0, 0.0, 0.0);
	//newmat->SetSpecularColour(0.0, 0.0, 0.0);
	//newmat->SetSpecPower(10);
	//newmat->SetCastShadow(false);
	//newobj->SetMaterial(newmat);
	//m_sceneObjects.push_back(newobj);
	//m_objectMaterials.push_back(newmat);

	//newobj = new Plane(); //an xz plane 40 units above, ceiling
	//static_cast<Plane*>(newobj)->SetPlane(Vector3(0.0, -1.0, 0.0), -40.0, true);
	//newobj->SetMaterial(newmat);
	//m_sceneObjects.push_back(newobj);

	//newmat = new Material();
	//newmat->SetAmbientColour(0.0, 0.0, 0.0);
	//newmat->SetDiffuseColour(0.0, 1.0, 0.0);
	//newmat->SetSpecularColour(0.0, 0.0, 0.0);
	//newmat->SetSpecPower(10);
	//newmat->SetCastShadow(false);
	//newobj->SetMaterial(newmat);


	//newobj = new TriMesh("../windmill.obj");
	//newmat = new Material();
	////mat for the box2
	//newmat->SetAmbientColour(0.0, 0.0, 0.0);
	//newmat->SetDiffuseColour(1, 1, 1);
	//newmat->SetSpecularColour(0.0, 0.0, 0.0);
	//Texture* Windmill_Diffuse = new Texture();
	//Windmill_Diffuse->LoadTextureFromFile("../windmill_diffuse.bmp");
	//newmat->SetDiffuseTexture(Windmill_Diffuse);
	//newmat->SetSpecPower(10);
	//newobj->SetMaterial(newmat);
	//m_sceneObjects.push_back(newobj);
	//m_objectMaterials.push_back(newmat);
	//m_Textures.push_back(Windmill_Diffuse);

//	newobj = new TriMesh("../terrain.obj");
//	newmat = new Material();
//	//mat for the box2
//	newmat->SetAmbientColour(0.0, 0.0, 0.0);
//	newmat->SetDiffuseColour(1, 1, 1);
//	newmat->SetSpecularColour(0.0, 0.0, 0.0);
//	Texture* terrain_Diffuse = new Texture();
//	terrain_Diffuse->LoadTextureFromFile("../terrain.bmp");
//	newmat->SetDiffuseTexture(terrain_Diffuse);
//	newmat->SetSpecPower(10);
//	newobj->SetMaterial(newmat);
////	m_sceneObjects.push_back(newobj);
//	m_objectMaterials.push_back(newmat);
//	m_Textures.push_back(terrain_Diffuse);

	Vector3 position(0, 0, 0);
	ObjLoader loader(position);
	newobj = new Box(position, 15, 15, 15);
	newobj->OverridePrimType(Primitive::PRIMTYPE_Bounding);
	m_sceneObjects.push_back(newobj);

	Mesh* mesh = loader.BuildMesh("../windmill.obj");
	Texture* testDiffuse = new Texture();
	testDiffuse->LoadTextureFromFile("../windmill_diffuse.bmp");
	for (int i = 0; i < mesh->m_Data.size(); i++) {
		newobj = mesh->m_Data[i];
		newmat = new Material();
		//mat for the box2
		newmat->SetAmbientColour(0.0, 0.0, 0.0);
		newmat->SetDiffuseColour(1.0, 1.0, 1.0);
		newmat->SetSpecularColour(0.0, 0.0, 0.0);
		newmat->SetReflectivity(0);
		newmat->SetRefractivity(0);
		newmat->SetSpecPower(10);
		newmat->SetDiffuseTexture(testDiffuse);
		newobj->SetMaterial(newmat);
		m_sceneObjects.push_back(newobj);
		m_objectMaterials.push_back(newmat);
	}
	Vector3 translation(0, 0, 0);
	ObjLoader churchloader(translation);
	newobj = new Box(translation, 15, 15, 15);
	newobj->OverridePrimType(Primitive::PRIMTYPE_Bounding);
	m_sceneObjects.push_back(newobj);

	Mesh* churchmesh = churchloader.BuildMesh("../house.obj");
	Texture* churchDiffuse = new Texture();
	churchDiffuse->LoadTextureFromFile("../house_diffuse.bmp");
	for (int i = 0; i < churchmesh->m_Data.size(); i++) {
		newobj = churchmesh->m_Data[i];
		newmat = new Material();
		//mat for the box2
		newmat->SetAmbientColour(0.0, 0.0, 0.0);
		newmat->SetDiffuseColour(1.0, 1.0, 1.0);
		newmat->SetSpecularColour(0.0, 0.0, 0.0);
		newmat->SetReflectivity(0);
		newmat->SetRefractivity(0);
		newmat->SetSpecPower(10);
		newmat->SetDiffuseTexture(churchDiffuse);
		newobj->SetMaterial(newmat);
		m_sceneObjects.push_back(newobj);
		m_objectMaterials.push_back(newmat);
	}
	Vector3 traintranslation(0, 0, -10);
	ObjLoader terrainloader(traintranslation);
	newobj = new Box(traintranslation, 150, 150, 150);
	newobj->OverridePrimType(Primitive::PRIMTYPE_Bounding);
	m_sceneObjects.push_back(newobj);

	Mesh* Terrain = terrainloader.BuildMesh("../terrain.obj");
	Texture* trDiffuse = new Texture();
	trDiffuse->LoadTextureFromFile("../terrain.bmp");
	for (int i = 0; i < Terrain->m_Data.size(); i++) {
		newobj = Terrain->m_Data[i];
		newmat = new Material();
		//mat for the box2
		newmat->SetAmbientColour(0.0, 0.0, 0.0);
		newmat->SetDiffuseColour(1.0, 1.0, 1.0);
		newmat->SetSpecularColour(0.0, 0.0, 0.0);
		newmat->SetReflectivity(0);
		newmat->SetRefractivity(0);
		newmat->SetSpecPower(10);
		newmat->SetDiffuseTexture(trDiffuse);
		newobj->SetMaterial(newmat);
		m_sceneObjects.push_back(newobj);
		m_objectMaterials.push_back(newmat);
	}

	//Vector3 fightyertranslation(0, 15, -25);
	//ObjLoader fighterloader(fightyertranslation);
	//newobj = new Box(fightyertranslation, 150, 150, 150);
	//newobj->OverridePrimType(Primitive::PRIMTYPE_Bounding);
	//m_sceneObjects.push_back(newobj);

	//Mesh* fighter = fighterloader.BuildMesh("../space_frigate_6.obj");
	////Texture* trDiffuse = new Texture();
	////trDiffuse->LoadTextureFromFile("../terrain.bmp");
	//for (int i = 0; i < fighter->m_Data.size(); i++) {
	//	newobj = fighter->m_Data[i];
	//	newmat = new Material();
	//	//mat for the box2
	//	newmat->SetAmbientColour(0.0, 0.0, 0.0);
	//	newmat->SetDiffuseColour(1.0, 1.0, 1.0);
	//	newmat->SetSpecularColour(0.0, 0.0, 0.0);
	//	newmat->SetReflectivity(0);
	//	newmat->SetRefractivity(0);
	//	newmat->SetSpecPower(10);
	////	newmat->SetDiffuseTexture(trDiffuse);
	//	newobj->SetMaterial(newmat);
	//	m_sceneObjects.push_back(newobj);
	//	m_objectMaterials.push_back(newmat);
	//}


	Light *newlight = new Light();
	newlight->SetLightPosition(0, 5, 10.0);
	newlight->SetLightColour(0.5, 0.5, 0.5);
	//	m_lights.push_back(newlight);
	//Create one light source for the scene
	newlight = new Light();
	newlight->SetLightPosition(0.0, 15.0, 10.0);
	m_lights.push_back(newlight);

	//A black background
	m_background.SetVector(0, 0, 0);

	//default scene width and height;
	m_sceneWidth = 1.33333333;
	m_sceneHeight = 1.0;

	//default camera position and look at
	m_activeCamera.SetPositionAndLookAt(Vector3(0.0, 10, 20), Vector3(0.0, 7.0, 0.0));
}


RayHitResult Scene::IntersectByRay(Ray& ray)
{
	RayHitResult result = Ray::s_defaultHitResult;
	RayHitResult tmp;

	std::vector<RayHitResult> hits;
	bool Cull_Triangles = true;
	for (int i = 0; i < m_sceneObjects.size(); i++) {

		if (m_sceneObjects[i]->m_primtype == Primitive::PRIMTYPE_Triangle && Cull_Triangles == true) {
			//ignore a triable this frame
			continue;
		}
		tmp = m_sceneObjects[i]->IntersectByRay(ray);

		if (tmp.data) {
			if (((Primitive*)tmp.data)->m_primtype == Primitive::PRIMTYPE_Bounding) {
			//	Cull_Triangles = false;
				continue;
			}
			if (isnan(tmp.point[0]) == false) {
				if (tmp.t > 0) {
					hits.push_back(tmp);
				}
			}
		}
	}
	if (hits.size() == 0) {
	//	printf("No Hits\n");
		return result;
	}
	for (int i = 0; i < hits.size() - 1; i++) {
		for (int j = 0; j < hits.size() - 1; j++) {
			if ((hits[j].t) > (hits[j + 1].t)) {
				std::swap(hits[j + 1], hits[j]);
			}
		}
	}
	if (hits.size() >= 1) {
		result = hits[0];
	}
	//TODO: Implement ray to scene intersection
	//All geometric objects are stored in m_sceneObjects.
	//To find out which object intersects with the ray
	//1. Enumerate through each primitive in m_sceneObjects
	//2. For each primitive, there is an IntersectByRay method which can be called to test for intersection
	//
	//Remember: a ray can potentially intersect with more than one object
	//We are only interested in the closest one, i.e. one with the smallest positive t
	//Check result.t for the parametric result of the interesection
	return result;
}
