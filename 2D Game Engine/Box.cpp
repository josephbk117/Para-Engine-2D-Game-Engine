#include "Box.h"
#include <Box2D\Box2D.h>

BoxCollider::BoxCollider()
{
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::init(const glm::vec2 & position, const glm::vec2 & dimension, const PhysicsMaterial& material, PhysicsBody bodyType = PhysicsBody::STATIC)
{
	this->dimension = dimension;
	b2BodyDef bodyDef;
	bodyDef.type = (b2BodyType)bodyType;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.linearDamping = material.linearDamping;
	bodyDef.angularDamping = material.angularDamping;
	body = Game::getPhysicsWorld()->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimension.x / 2.0f, dimension.y / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = material.density;
	fixtureDef.friction = material.friction;
	fixtureDef.restitution = material.bounciness;

	body->SetSleepingAllowed(false);
	fixture = body->CreateFixture(&fixtureDef);
}

void BoxCollider::setPhysicsMaterial(const PhysicsMaterial & physicsMaterial)
{
	fixture->SetDensity(physicsMaterial.density);
	fixture->SetFriction(physicsMaterial.friction);
	fixture->SetRestitution(physicsMaterial.bounciness);
	body->SetLinearDamping(physicsMaterial.linearDamping);
	body->SetAngularDamping(physicsMaterial.angularDamping);
}

void BoxCollider::canRotate(bool canObjectRotate)const
{
	body->SetFixedRotation(canObjectRotate);
}

void BoxCollider::applyTorque(float strength)
{
	body->ApplyTorque(strength, true);
}

void BoxCollider::applyForce(const glm::vec2& force)
{
	body->ApplyForceToCenter(b2Vec2(force.x, force.y), true);
}

void BoxCollider::setVelocity(const glm::vec2& velocity)
{
	body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
}

void BoxCollider::setAngularVelocity(float velocity)
{
	body->SetAngularVelocity(velocity);
}

const glm::vec2 & BoxCollider::getDimensions()const
{
	return dimension;
}

const float BoxCollider::getAngle() const
{
	return body->GetAngle();
}

const glm::vec2 BoxCollider::getPosition() const
{
	return glm::vec2(body->GetPosition().x, body->GetPosition().y);
}

const PhysicsBody BoxCollider::getPhysicsType() const
{
	switch (body->GetType())
	{
	case b2BodyType::b2_staticBody:
		return PhysicsBody::STATIC;
	case b2BodyType::b2_kinematicBody:
		return PhysicsBody::KINEMATIC;
	case b2BodyType::b2_dynamicBody:
		return PhysicsBody::DYNAMIC;
	default:
		return PhysicsBody::STATIC;
	}
}
