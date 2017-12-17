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
	PhysicsMaterial(float angularDamping = 0.0f, float linearDamping = 0.0f, float density = 1.0f, float friction = 0.0f, float bounciness = 0.0f)
	{
		this->angularDamping = angularDamping;
		this->linearDamping = linearDamping;
		this->density = density;
		this->friction = friction;
		this->bounciness = bounciness;
	}
};