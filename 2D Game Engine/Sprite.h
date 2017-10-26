#pragma once
#include <GL\glew.h>
#include <GLM\common.hpp>
#include "Component.h"
#include <iostream>
class Sprite : public Component
{
public:
	Sprite();
	~Sprite();
	void init(float width, float height);
	void draw();
	void setTextureID(unsigned int textureID);
	glm::vec2 getDimensions();
	void setDimension(glm::vec2 newDimension);
private:
	float width, height, x, y;
	GLuint vboID;
	GLuint textureID;
	void setUpSpriteDimensions(float width, float height);
};

