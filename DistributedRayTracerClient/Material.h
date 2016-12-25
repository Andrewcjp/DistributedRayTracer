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

#include <stdlib.h>

#include "Vector3.h"
#include <ios>
#include <iostream>
#include <fstream> 
#include <vector>
#include "Vector3d.h"
typedef Vector3 Colour;

//class representing a texture in TinyRay
class Texture
{
public:
	enum TEXUNIT
	{
		TEXUNIT_DIFFUSE = 0,
		TEXUNIT_NORMAL = 1
	};
private:
	std::vector<std::uint8_t> Pixels;
public:
	unsigned int	mWidth;			//width of the image
	unsigned int    mHeight;		//height of the image
	 int    mChannels = 3;		//number of channels in the image either 3 or 4, i.e. RGB or RGBA
	unsigned char*	mImage;			//image data
	int msize;
	Colour GetBiLinearFilteredColour(double u, double v);
	Texture()
	{
		mImage = NULL;
	}
	Texture(char* filename) {
		mImage = NULL;
		LoadTextureFromFile(filename);
	}

	~Texture()
	{
		if (mImage) delete[] mImage;
	}

	Colour GetTexelColour(double u, double v);
	
	//todo: covert to format
	void LoadTextureFromFile(char* filename,bool tga = false);
};

//Class representing a material in TinyRay
class Material
{
private:
	Colour mAmbient;					//Ambient colour of the material
	Colour mDiffuse = Colour(1,0,0);	//Diffuse colour of the material
	Colour mSpecular;					//Specular colour of the material
	double mSpecpower;					//Specular power of the material
	Texture* mDiffuse_texture;			//Colour (diffuse) texture of the material for texture mapped primitives
	Texture* mNormal_texture;			//Normal texture of the material for textured mapped privmites with a normal map
	bool mCastShadow;					//boolean indicating if a material can cast shadow
	double mReflectivity;
	double mRefractiveIndex;

public:
	Colour mAO;
	Material();
	~Material();

	void SetDefaultMaterial();
	void SetAmbientColour(float r, float g, float b);
	void SetDiffuseColour(float r, float g, float b);
	void SetSpecularColour(float r, float g, float b);
	void SetSpecPower(double spow);
	inline void SetDiffuseTexture(Texture* tex) {
		mDiffuse_texture = tex;
	}
	inline void SetNormalTexture(Texture* tex) {
		mNormal_texture = tex;
	}
	inline Texture* GetDiffuseTexture() {
		return mDiffuse_texture;
	}
	inline Texture* GetNormalTexture() {
		return mDiffuse_texture;
	}
	inline void SetCastShadow(bool castShadow)
	{
		mCastShadow = castShadow;
	}
	inline void SetReflectivity(double amt) {
		mReflectivity = amt;
	}
	inline void SetRefractivity(double amt) {
		mRefractiveIndex = amt;
	}
	inline double GetReflectivity() {
		return	mReflectivity;
	}
	inline double GetRefractivity() {
		return mRefractiveIndex;
	}
	inline Colour& GetAmbientColour()
	{
		return mAmbient;
	}

	inline Colour& GetDiffuseColour()
	{
		return mDiffuse;
	}

	inline Colour& GetSpecularColour()
	{
		return mSpecular;
	}

	inline double GetSpecPower()
	{
		return mSpecpower;
	}

	inline bool CastShadow()
	{
		return mCastShadow;
	}

	inline bool HasDiffuseTexture()
	{
		return mDiffuse_texture != NULL;
	}

	inline bool HasNormalTexture()
	{
		return mNormal_texture != NULL;
	}
};

