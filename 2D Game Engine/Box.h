#pragma once
#include <Box2D\Box2D.h>
#include <Box2D\Dynamics\b2Body.h>
#include <GLM\glm.hpp>
#include <GL\glew.h>
#include "Component.h"
#include "Game.h"
#include "PhysicsData.h"

class BoxCollider : public Component
{
public:
	BoxCollider();
	~BoxCollider();
	void init(const glm::vec2 &position, const glm::vec2 &dimension, PhysicsBody bodyType, float density);
	b2Body* getBody();
	b2Fixture* getFixture();
	const glm::vec2& getDimensions();
private:
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;
	glm::vec2 dimension;
};

