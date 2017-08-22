#pragma once
#include <Box2D\Box2D.h>
#include <GLM\glm.hpp>
class Box
{
public:
	Box();
	~Box();
	void init(b2World *world, const glm::vec2 &position, const glm::vec2 &dimension);
	b2Body* getBody();
	b2Fixture* getFixture();
	const glm::vec2& getDimensions();
private:
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;
	glm::vec2 dimensions;
};

