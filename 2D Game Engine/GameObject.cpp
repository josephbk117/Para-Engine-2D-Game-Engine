#include "GameObject.h"

GameObject::GameObject()
{
	this->name = "";
	this->objectID = NULL;
}

GameObject::GameObject(const std::string & name, unsigned int objectID)
{
	this->name = name;
	this->objectID = objectID;
}


void GameObject::addComponent(Component * comp)
{
	components.push_back(comp);
}

GameObject::~GameObject()
{
}
