#pragma once
#include <Box2D\Box2D.h>
enum class PhysicsBody
{
	STATIC = b2BodyType::b2_staticBody,
	KINEMATIC = b2BodyType::b2_kinematicBody,
	DYNAMIC = b2BodyType::b2_dynamicBody
};
struct PhysicsMaterial
{
	float angularDamping;
	float linearDamping;
	float density;
	float friction;
	float bounciness;
	PhysicsMaterial(float angularDamping, float linearDamping, float density, float friction,float bounciness)
	{
		this->angularDamping = angularDamping;
		this->linearDamping = linearDamping;
		this->density = density;
		this->friction = friction;
		this->bounciness = bounciness;
	}
	PhysicsMaterial( float density, float friction, float bounciness)
	{
		this->angularDamping = 0.0f;
		this->linearDamping = 0.0f;
		this->density = density;
		this->friction = friction;
		this->bounciness = bounciness;
	}
};