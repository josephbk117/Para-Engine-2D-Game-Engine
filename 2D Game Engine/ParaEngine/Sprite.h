#pragma once
#include <GLM\common.hpp>
class Component;
#include "Component.h"
class Sprite : public Component
{
public:
	Sprite();
	~Sprite();
	void init(float width, float height);
	void setTextureID(unsigned int textureID);
	unsigned int getTextureID()const noexcept;
	glm::vec2 getDimensions() const;
	void setDimension(const glm::vec2& newDimension);
	void setDimension(float width, float height);
	void draw();
private:
	float width, height;
	unsigned int vaoID;
	unsigned int vboID;
	unsigned int textureID;
	void setUpSpriteDimensions(float width, float height);
};

