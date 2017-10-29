#pragma once
#include <iostream>
#include <GL\glew.h>
#include <unordered_map>
#include "stb_image.h"
class TextureManager
{
public:
	static unsigned int loadTextureFromFile(const std::string& path, const std::string& referenceString, bool gamma);
	static unsigned int getTextureFromReference(const std::string& referenceString);
	static void unloadTexturesFromMemory();
private:
	static std::unordered_map<std::string ,unsigned int> textureIdMap;
};