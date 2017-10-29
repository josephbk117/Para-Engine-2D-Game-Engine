#include "GameObject.h"

std::unordered_map<std::string, GameObject*> GameObject::gameObjectMap;
std::vector<GameObject *> GameObject::gameObjectVector;
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
	for (int i = 0; i < components.size(); i++)
		delete components[i];
}
