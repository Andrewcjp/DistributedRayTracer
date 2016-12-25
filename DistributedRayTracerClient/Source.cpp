//#include <stdio.h>
//#include "Scene.h"
//#include "RayTracer.h"
//class MyClass
//{
//public:
//	MyClass();
//	~MyClass();
//
//	void Initilise(int width, int height);
//
//private:
//	Scene* scene;
//	RayTracer* rtracer;
//};
//
//MyClass::MyClass()
//{
//}
//
//MyClass::~MyClass()
//{
//}
//void MyClass::Initilise(int width, int height) {
//	rtracer = new RayTracer(width, height);
//	scene = new Scene();
//	scene->InitDefaultScene();
//	scene->SetSceneWidth((float)width / (float)height);
//	rtracer->DoRayTrace(scene);
//}
//
//int main() {
//	MyClass* cla = new MyClass();
//	cla->Initilise(100, 100);
//	
//	getchar();
//	return 0;
//}