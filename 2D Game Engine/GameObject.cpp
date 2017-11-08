#include "GameObject.h"
#include <iostream>

std::unordered_map<std::string, GameObject*> GameObject::gameObjectMap;
std::vector<GameObject *> GameObject::gameObjectVector;
std::vector<GameObject *> GameObject::objectsMarkedForDeletion;
bool GameObject::isDirty = false;

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
	comp->attachedGameObject = this;
	components.push_back(comp);
}

GameObject::~GameObject()
{
	for (unsigned int i = 0; i < components.size(); i++)
		delete components[i];
}
