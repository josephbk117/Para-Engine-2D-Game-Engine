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
	void init(const glm::vec2 &position, const glm::vec2 &dimension, const PhysicsMaterial& material, const PhysicsBody& bodyType);
	virtual void start();
	void setPhysicsMaterial(const PhysicsMaterial& physicsMaterial) noexcept;
	void setRotationConstraint(bool canObjectRotate)const noexcept;
	void applyTorque(float strength) noexcept;
	void applyForce(const glm::vec2& force) noexcept;
	void setVelocity(const glm::vec2& velocity) noexcept;
	void setAngularVelocity(float velocity) noexcept;
	void setPosition(const glm::vec2& position) noexcept;
	void setRotation(float rotation) noexcept;
	const glm::vec2& getDimensions()const noexcept;
	const float getAngle()const noexcept;
	const glm::vec2 getPosition()const noexcept;
	const PhysicsBody getPhysicsType()const noexcept;

private:
	struct InternalAcess;
	InternalAcess* access = nullptr;
};

