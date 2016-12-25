#include <stdlib.h>
#include "Framebuffer.h"

Framebuffer::Framebuffer()
{
	mWidth = 0;
	mHeight = 0;
	mColourBuffer = NULL;
}

Framebuffer::Framebuffer(int width, int height)
{
	InitFramebuffer(width, height);
}

Framebuffer::~Framebuffer()
{
	delete[] mColourBuffer;
}

void Framebuffer::WriteRGBToFramebuffer(const Colour & colour, int x, int y)
{
	int offset = y*mWidth + x;
	*(mColourBuffer + offset) = colour;
}
Colour Framebuffer::ReadRGBFromFramebuffer( int x, int y)
{
	int offset = y*mWidth + x;
	return *(mColourBuffer + offset);
}
void Framebuffer::InitFramebuffer(int width, int height)
{
	mWidth = width;
	mHeight = height;
	mColourBuffer = new Colour[width*height];
}
