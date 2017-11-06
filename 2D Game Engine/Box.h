#pragma once
#include <GLM\glm.hpp>
#include "Component.h"
#include "Game.h"
#include "PhysicsData.h"

class BoxCollider : public Component
{
public:
	BoxCollider();
	~BoxCollider();
	void init(const glm::vec2 &position, const glm::vec2 &dimension, const PhysicsMaterial& material, PhysicsBody bodyType);
	void setPhysicsMaterial(const PhysicsMaterial& physicsMaterial);
	void setRotationConstraint(bool canObjectRotate)const;
	void applyTorque(float strength);
	void applyForce(const glm::vec2& force);
	void setVelocity(const glm::vec2& velocity);
	void setAngularVelocity(float velocity);
	void setPosition(const glm::vec2& position);
	void setRotation(const float& rotation);
	const glm::vec2& getDimensions()const;
	const float getAngle()const;
	const glm::vec2 getPosition()const;
	const PhysicsBody getPhysicsType()const;
private:
	struct InternalAcess;
	InternalAcess* access = nullptr;
};

