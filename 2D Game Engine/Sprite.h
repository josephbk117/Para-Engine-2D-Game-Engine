#pragma once
#include <GL\glew.h>
#include <GLM\common.hpp>
class Sprite
{
public:
	Sprite();
	~Sprite();
	void init(float x, float y, float width, float height);
	void draw();
	glm::vec2 getPosition();
	glm::vec2 getDimensions();
	void setPosition(glm::vec2 newPosition);
private:
	float x, y, width, height;
	GLuint vboID;
};

