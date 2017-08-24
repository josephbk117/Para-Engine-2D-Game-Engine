#include "Circle.h"



Circle::Circle()
{
}


Circle::~Circle()
{
}
void Circle::init(b2World * world, const glm::vec2 & position, float radius)
{
	this->radius = radius;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	body = world->CreateBody(&bodyDef);

	b2CircleShape circleShape;
	circleShape.m_p.Set(0, 0);
	circleShape.m_radius = 1;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 1.4;
	fixtureDef.friction = 0.3;

	fixture = body->CreateFixture(&fixtureDef);
}

b2Fixture * Circle::getFixture()
{
	return fixture;
}

float Circle::getRadius()
{
	return radius;
}

void Circle::draw()
{
	glm::vec2 center = 
}

b2Body * Circle::getBody()
{
	return body;
}
