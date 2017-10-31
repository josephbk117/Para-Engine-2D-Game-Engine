#pragma once

enum class PhysicsBody
{
	STATIC = 0,
	KINEMATIC,
	DYNAMIC
};

struct PhysicsMaterial
{
	float angularDamping;
	float linearDamping;
	float density;
	float friction;
	float bounciness;
	PhysicsMaterial(float angularDamping, float linearDamping, float density, float friction, float bounciness)
	{
		this->angularDamping = angularDamping;
		this->linearDamping = linearDamping;
		this->density = density;
		this->friction = friction;
		this->bounciness = bounciness;
	}
	PhysicsMaterial(float density, float friction, float bounciness)
	{
		this->angularDamping = 0.0f;
		this->linearDamping = 0.0f;
		this->density = density;
		this->friction = friction;
		this->bounciness = bounciness;
	}
};