#include "GameObject.h"

GameObject::GameObject()
{
	this->name = "";
	this->layerOrder = 0;
}

GameObject::GameObject(const std::string & name)
{
	this->name = name;
}

void GameObject::addComponent(Component * comp)
{
	components.push_back(comp);
}

GameObject::~GameObject()
{
}
