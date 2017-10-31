#pragma once
#include <GLM\common.hpp>
#include "Component.h"
class Sprite : public Component
{
public:
	Sprite();
	~Sprite();
	void init(float width, float height);
	void setTextureID(unsigned int textureID);
	unsigned int getTextureID()const;
	glm::vec2 getDimensions() const;
	void setDimension(glm::vec2 newDimension);
	void draw();
private:
	float width, height;
	unsigned int vboID;
	unsigned int textureID;
	void setUpSpriteDimensions(float width, float height);
};

