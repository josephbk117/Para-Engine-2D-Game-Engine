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
	circleShape.m_radius = radius;

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
	glm::vec2 center = glm::vec2(body->GetPosition().x, body->GetPosition().y);
	int segmentCount = 10;
	float incVal = (2.0*(22.0 / 7.0)) / (float)segmentCount;

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < segmentCount; i++)
	{
		float xVal = center.x + (radius * (glm::sin(i * incVal)));
		float yVal = center.y + (radius * (glm::cos(i * incVal)));
		glVertex2f(xVal, yVal);
	}
	glEnd();
}

b2Body * Circle::getBody()
{
	return body;
}
