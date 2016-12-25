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

#include "Material.h"
#include "Ray.h"
#include "Scene.h"
#include "Framebuffer.h"


//min max funcs
#ifndef NOMINMAX

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#endif  /* NOMINMAX */

class RayTracer
{
private:
	Framebuffer		*m_framebuffer;
	int				m_buffWidth;
	int				m_buffHeight;
	int				m_renderCount;
	int				m_traceLevel;
	int				m_Offsetx = 0;
	int				m_Offsety = 0;
	
	//Trace the scene from a given ray and scene
	//Params:
	//	Scene* pScene		pointer to the scene being traced
	//  Ray& ray			reference to an input ray
	//  Colour incolour		default colour to use when the ray does not intersect with any objects
	//  int tracelevel		the current recursion level of the TraceScene call
	//  bool shadowray		true if the input ray is a shadow ray, could be useful when handling shadows
	Colour TraceScene(Scene* pScene, Ray& ray, Colour incolour, int tracelevel, bool shadowray = false);



	//Compute lighting for a given ray-primitive intersection result
	//Params:
	//			std::vector<Light*>* lights     pointer to a list of active light sources
	//			Vector3*	pointer to the active camera
	//			RayHitResult* hitresult		Hit result from ray-primitive intersection
	Colour CalculateLighting(std::vector<Light*>* lights, Vector3d * campos, RayHitResult * hitresult);

	//extra options 
	bool SuperSample = false;
	bool Softshadows = false;
	bool normalmapping = false;
	bool AmbientOcclusion = false;
	int AAFactor = 3;
public:
	double TimeinMS = 0;
	enum TraceFlags
	{
		TRACE_AMBIENT = 0x1,					//trace ambient colour only
		TRACE_DIFFUSE_AND_SPEC = 0x1 << 1,		//trace and compute diffuse and specular lighting components 
		TRACE_SHADOW = 0x1 << 2,				//trace shadow rays
		TRACE_REFLECTION = 0x1 << 3,			//trace reflection rays
		TRACE_REFRACTION = 0x1 << 4,			//trace refraction rays
	};

	TraceFlags m_traceflag;						//current trace flags value default is TRACE_AMBIENT

	RayTracer();
	RayTracer(int width, int height);
	RayTracer(int width, int height,int offsetx,int offsety);
	~RayTracer();
	inline void SetExtra(bool AA, bool softshadows, bool nrmmapping) {
		SuperSample = AA;
		Softshadows = softshadows;
		normalmapping = nrmmapping;
	}
	inline void SetAAFactor(int factor) {
		std::cout << "Setting AA factor to " << factor << std::endl;
		AAFactor = factor;
	}
	inline void ToggleNormalMapping() {

		if (normalmapping) {
			std::cout << "Normal Mapping Disabled" << std::endl;
			normalmapping = false;
		}
		else {
			std::cout << "Normal Mapping Enabled" << std::endl;
			normalmapping = true;
		}
	}
	inline void ToggleSoftShadows() {

		if (Softshadows) {
			std::cout << "Soft Shadows Disabled" << std::endl;
			Softshadows = false;
		}
		else {
			std::cout << "Soft Shadows Enabled" << std::endl;
			Softshadows = true;
		}
	}
	inline void ToggleSuperSample() {
		if (SuperSample) {
			std::cout << "Super Sampling Disabled" << std::endl;
			SuperSample = false;
		}
		else {
			std::cout << "Super Sampling Enabled" << std::endl;
			SuperSample = true;
		}
	}
	inline void ToggleAmbientOcclusion() {
		if (AmbientOcclusion) {
			std::cout << "Ambient Occlusion Disabled" << std::endl;
			AmbientOcclusion = false;
		}
		else {
			std::cout << "Ambient Occlusion Enabled" << std::endl;
			AmbientOcclusion = true;
		}
	}
	inline void SetTraceLevel(int level)		//Set the level of recursion, default is 5
	{
		m_traceLevel = level;
	}

	inline void ResetRenderCount()
	{
		m_renderCount = 0;
	}

	inline Framebuffer *GetFramebuffer() const
	{
		return m_framebuffer;
	}

	//Trace a given scene
	//Params: Scene* pScene   Pointer to the scene to be ray traced
	void DoRayTrace(Scene* pScene);
};

