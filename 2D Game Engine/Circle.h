#pragma once
#include <Box2D\Box2D.h>
#include <GLM\glm.hpp>
#include <GL\glew.h>
class Circle
{
public:
	Circle();
	~Circle();
	void init(b2World *world, const glm::vec2 &position, float radius);
	b2Body* getBody();
	b2Fixture* getFixture();
	float getRadius();
	void draw();
private:
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;
	float radius;
};

