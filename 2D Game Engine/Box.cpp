#include "Box.h"

BoxCollider::BoxCollider()
{
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::init(const glm::vec2 & position, const glm::vec2 & dimension, PhysicsBody bodyType, float density)
{
	this->dimension = dimension;
	b2BodyDef bodyDef;
	bodyDef.type = (b2BodyType)bodyType;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.linearDamping = 0.0f;
	bodyDef.angularDamping = 0.0f;
	body = Game::getPhysicsWorld()->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimension.x / 2.0f, dimension.y / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	fixture = body->CreateFixture(&fixtureDef);
}

b2Fixture * BoxCollider::getFixture()
{
	return fixture;
}

const glm::vec2 & BoxCollider::getDimensions()
{
	return dimension;
}

b2Body * BoxCollider::getBody()
{
	return body;
}
