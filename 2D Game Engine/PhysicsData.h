#pragma once
#include <Box2D\Box2D.h>
enum class PhysicsBody
{
	STATIC = b2BodyType::b2_staticBody,
	KINEMATIC = b2BodyType::b2_kinematicBody,
	DYNAMIC = b2BodyType::b2_dynamicBody
};