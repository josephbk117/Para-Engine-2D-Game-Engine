#include "GameObject.h"


GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::drawObject()
{
	sprite.setPosition(glm::vec2(boxCollider.getBody()->GetPosition().x, boxCollider.getBody()->GetPosition().y));
	sprite.draw();
}
