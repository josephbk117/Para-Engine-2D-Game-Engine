#include "Box.h"

Box::Box()
{
}

Box::~Box()
{
}

void Box::init(b2World * world, const glm::vec2 & position, const glm::vec2 & dimension)
{
	dimensions = dimension;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	body = world->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimension.x / 2.0, dimension.y / 2.0);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.4;
	fixtureDef.friction = 0.3;

	fixture = body->CreateFixture(&fixtureDef);
}

b2Fixture * Box::getFixture()
{
	return fixture;
}

const glm::vec2 & Box::getDimensions()
{
	return dimensions;
}

void Box::draw()
{
	glm::vec4 destRect;
	destRect.x = getBody()->GetPosition().x;
	destRect.y = getBody()->GetPosition().y;
	destRect.z = getDimensions().x;
	destRect.w = getDimensions().y;

	glBegin(GL_QUADS);
	glVertex2f(destRect.x, destRect.y);
	glVertex2f(destRect.x + destRect.z, destRect.y);
	glVertex2f(destRect.x + destRect.z, destRect.y + destRect.w);
	glVertex2f(destRect.x, destRect.y + destRect.w);
	glEnd();
}

b2Body * Box::getBody()
{
	return body;
}
