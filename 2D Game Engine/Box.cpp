#include "Box.h"
#include <Box2D\Box2D.h>

struct BoxCollider::InternalAcess
{
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;
	glm::vec2 dimension;
};

BoxCollider::BoxCollider()
{
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::init(const glm::vec2 & position, const glm::vec2 & dimension, const PhysicsMaterial& material, PhysicsBody bodyType = PhysicsBody::STATIC)
{
	acess = new InternalAcess;
	acess->dimension = dimension;
	b2BodyDef bodyDef;
	bodyDef.type = (b2BodyType)bodyType;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.linearDamping = material.linearDamping;
	bodyDef.angularDamping = material.angularDamping;
	acess->body = Game::getPhysicsWorld()->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimension.x / 2.0f, dimension.y / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = material.density;
	fixtureDef.friction = material.friction;
	fixtureDef.restitution = material.bounciness;

	acess->body->SetSleepingAllowed(false);
	acess->fixture = acess->body->CreateFixture(&fixtureDef);
}

void BoxCollider::setPhysicsMaterial(const PhysicsMaterial & physicsMaterial)
{
	acess->fixture->SetDensity(physicsMaterial.density);
	acess->fixture->SetFriction(physicsMaterial.friction);
	acess->fixture->SetRestitution(physicsMaterial.bounciness);
	acess->body->SetLinearDamping(physicsMaterial.linearDamping);
	acess->body->SetAngularDamping(physicsMaterial.angularDamping);
}

void BoxCollider::setRotationConstraint(bool canObjectRotate)const
{
	acess->body->SetFixedRotation(canObjectRotate);
}

void BoxCollider::applyTorque(float strength)
{
	acess->body->ApplyTorque(strength, true);
}

void BoxCollider::applyForce(const glm::vec2& force)
{
	acess->body->ApplyForceToCenter(b2Vec2(force.x, force.y), true);
}

void BoxCollider::setVelocity(const glm::vec2& velocity)
{
	acess->body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
}

void BoxCollider::setAngularVelocity(float velocity)
{
	acess->body->SetAngularVelocity(velocity);
}

const glm::vec2 & BoxCollider::getDimensions()const
{
	return acess->dimension;
}

const float BoxCollider::getAngle() const
{
	return acess->body->GetAngle();
}

const glm::vec2 BoxCollider::getPosition() const
{
	return glm::vec2(acess->body->GetPosition().x, acess->body->GetPosition().y);
}

const PhysicsBody BoxCollider::getPhysicsType() const
{
	switch (acess->body->GetType())
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
