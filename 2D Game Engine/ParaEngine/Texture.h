#pragma once
struct  Texture
{
	Texture(unsigned texId, unsigned width, unsigned height) 
	{
		this->textureId = texId;
		this->width = width;
		this->height = height;
	}
	unsigned int textureId;
	unsigned int width;
	unsigned int height;
};