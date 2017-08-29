#pragma once
#include <iostream>
#include <GL\glew.h>
#include "stb_image.h"
class TextureLoader
{
public:	
	static unsigned int loadTextureFromFile(const std::string& path, bool gamma);
};

