#include "Box.h"

Box::Box()
{
}

Box::~Box()
{
}

void Box::init(b2World * world, const glm::vec2 & position, const glm::vec2 & dimension, b2BodyType bodyType, float density)
{
	this->dimension = dimension;
	b2BodyDef bodyDef;
	bodyDef.type = bodyType;
	bodyDef.position.Set(position.x, position.y);
	body = world->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimension.x / 2.0f, dimension.y / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = density;
	fixtureDef.friction = 0.3f;

	fixture = body->CreateFixture(&fixtureDef);
}

b2Fixture * Box::getFixture()
{
	return fixture;
}

const glm::vec2 & Box::getDimensions()
{
	return dimension;
}

b2Body * Box::getBody()
{
	return body;
}
