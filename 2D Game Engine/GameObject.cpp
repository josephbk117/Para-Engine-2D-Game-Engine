#include "GameObject.h"
#include "Box.h"
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
void GameObject::removeAllObjectsMarkedForDeletion()
{
	if (objectsMarkedForDeletion.size() <= 0)
		return;
	unsigned int deletionSize = objectsMarkedForDeletion.size();
	for (unsigned int i = 0; i < deletionSize; i++)
	{
		for (unsigned int j = 0; i < gameObjectVector.size(); j++)
		{
			if (objectsMarkedForDeletion[i] != nullptr)
			{
				if (gameObjectVector[j] == objectsMarkedForDeletion[i])
				{
					std::string name = objectsMarkedForDeletion[i]->getName();
					gameObjectMap.erase(name);
					delete objectsMarkedForDeletion[i];
					break;
				}
			}
		}
	}

	gameObjectVector.clear();
	for (auto it = gameObjectMap.begin(); it != gameObjectMap.end(); ++it)
	{
		if (it->second != nullptr)
			gameObjectVector.push_back(it->second);
	}
	objectsMarkedForDeletion.clear();
}
GameObject::~GameObject()
{
	for (unsigned int i = 0; i < components.size(); i++)
		delete components[i];
}
