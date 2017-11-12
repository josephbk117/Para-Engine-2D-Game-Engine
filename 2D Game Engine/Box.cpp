#include <iostream>
#include "Box.h"
#include <Box2D\Box2D.h>

struct BoxCollider::InternalAcess : public b2ContactListener
{
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;
	GameObject* attachedObject = nullptr;
	glm::vec2 dimension;
};

BoxCollider::BoxCollider()
{
}

BoxCollider::~BoxCollider()
{
	access->body->GetWorld()->DestroyBody(access->body);
}

void BoxCollider::init(const glm::vec2 & position, const glm::vec2 & dimension, const PhysicsMaterial& material, PhysicsBody bodyType = PhysicsBody::STATIC)
{
	access = new InternalAcess;
	access->dimension = dimension;
	b2BodyDef bodyDef;
	bodyDef.type = (b2BodyType)bodyType;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.linearDamping = material.linearDamping;
	bodyDef.angularDamping = material.angularDamping;
	access->body = Game::getPhysicsWorld()->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimension.x / 2.0f, dimension.y / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = material.density;
	fixtureDef.friction = material.friction;
	fixtureDef.restitution = material.bounciness;

	access->body->SetSleepingAllowed(false);
	access->fixture = access->body->CreateFixture(&fixtureDef);
	access->body->GetWorld()->SetContactListener(access);
}

void BoxCollider::start()
{
	std::cout << "\nGame object : " << attachedGameObject->getName().c_str();
	access->attachedObject = attachedGameObject;
	access->body->SetUserData(attachedGameObject);
}

void BoxCollider::setPhysicsMaterial(const PhysicsMaterial & physicsMaterial)
{
	access->fixture->SetDensity(physicsMaterial.density);
	access->fixture->SetFriction(physicsMaterial.friction);
	access->fixture->SetRestitution(physicsMaterial.bounciness);
	access->body->SetLinearDamping(physicsMaterial.linearDamping);
	access->body->SetAngularDamping(physicsMaterial.angularDamping);
}

void BoxCollider::setRotationConstraint(bool canObjectRotate)const
{
	access->body->SetFixedRotation(canObjectRotate);
}

void BoxCollider::applyTorque(float strength)
{
	access->body->ApplyTorque(strength, true);
}

void BoxCollider::applyForce(const glm::vec2& force)
{
	access->body->ApplyForceToCenter(b2Vec2(force.x, force.y), true);
}

void BoxCollider::setVelocity(const glm::vec2& velocity)
{
	access->body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
}

void BoxCollider::setAngularVelocity(float velocity)
{
	access->body->SetAngularVelocity(velocity);
}

void BoxCollider::setPosition(const glm::vec2 & position)
{
	access->body->SetTransform(b2Vec2(position.x, position.y), access->body->GetAngle());
}

void BoxCollider::setRotation(const float & rotation)
{
	access->body->SetTransform(access->body->GetPosition(), rotation);
}

const glm::vec2 & BoxCollider::getDimensions()const
{
	return access->dimension;
}

const float BoxCollider::getAngle() const
{
	return access->body->GetAngle();
}

const glm::vec2 BoxCollider::getPosition() const
{
	return glm::vec2(access->body->GetPosition().x, access->body->GetPosition().y);
}

const PhysicsBody BoxCollider::getPhysicsType() const
{
	switch (access->body->GetType())
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