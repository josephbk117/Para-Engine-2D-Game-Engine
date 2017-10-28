#pragma once
#include <Box2D\Box2D.h>
#include <GLM\glm.hpp>
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
	void canRotate(bool canObjectRotate);
	void applyTorque(float strength);
	void applyForce(glm::vec2 force);
	void setVelocity(glm::vec2 velocity);
	void setAngularVelocity(float velocity);
	const glm::vec2& getDimensions();
private:
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;
	glm::vec2 dimension;
};

