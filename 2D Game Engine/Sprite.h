#pragma once
#include <GL\glew.h>
#include <GLM\common.hpp>
#include "Component.h"
class Sprite : public Component
{
public:
	Sprite();
	~Sprite();
	void init(float x, float y, float width, float height);
	void draw();
	void setTextureID(unsigned int textureID);
	void setDrawOrder(int order);
	int getDrawOrder();
	glm::vec2 getPosition();
	glm::vec2 getDimensions();
	void setPosition(glm::vec2 newPosition);
	void setDimension(glm::vec2 newDimension);
private:
	float x, y, width, height;
	GLuint vboID;
	GLuint textureID;
	int drawOrder;
	void setUpSpriteDimensions(float width, float height);
};

