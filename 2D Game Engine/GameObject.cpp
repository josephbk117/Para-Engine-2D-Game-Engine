#include "GameObject.h"
#include "Transform.h"
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

void GameObject::setName(const std::string & name) noexcept
{
	isDirty = true; 
	this->name = name;
}

const std::string & GameObject::getName() const noexcept
{
	return name;
}

void GameObject::setLayerOrder(int order) noexcept
{
	isDirty = true; 
	this->layerOrder = order;
}

const int GameObject::getLayerOrder() const noexcept
{
	return layerOrder;
}

void GameObject::addComponent(Component * comp)
{
#if _DEBUG
	if (typeCountMap.find(std::string(typeid(*comp).name())) == typeCountMap.end())
		typeCountMap[std::string(typeid(*comp).name())] = 0;
	else
	{
		typeCountMap[std::string(typeid(*comp).name())] = typeCountMap[std::string(typeid(*comp).name())] + 1;
		throw("More than one component one of type was added");
	}
#endif

	comp->attachedGameObject = this;
	components.push_back(comp);
}
const std::vector<Component*>& GameObject::getAttachedComponents()
{
	return components;
}
GameObject * GameObject::getGameObjectWithName(const std::string & name)
{
#if _DEBUG
	if (gameObjectMap.find(name) == gameObjectMap.end())
		throw ("No Such Game Object Exists");
#endif
	return gameObjectMap[name];
}
GameObject * GameObject::createGameObject(const std::string & name, bool isUI)
{
#if _DEBUG
	if (gameObjectMap.find(name) != gameObjectMap.end())
		throw("Same name already exists");
#endif
	isDirty = true;
	GameObject* gameObject = new GameObject(name);
	gameObject->addComponent(new Transform);
	gameObject->isPartOfUI = isUI;
	gameObjectMap[name] = gameObject;
	gameObjectVector.push_back(gameObject);
	return gameObject;
}
const std::vector<GameObject*>& GameObject::getAllGameObjects() noexcept
{
	return gameObjectVector;
}
void GameObject::deleteGameObjectWithName(const std::string & name)
{
	if (gameObjectMap.find(name) == gameObjectMap.end())
		return;
	bool canAdd = true;
	const unsigned int objDeletionSize = objectsMarkedForDeletion.size();
	for (unsigned int i = 0; i < objDeletionSize; i++)
	{
		if (gameObjectMap[name] == objectsMarkedForDeletion[i])
		{
			canAdd = false;
			break;
		}
	}
	if (canAdd)
	{
		objectsMarkedForDeletion.push_back(gameObjectMap[name]);
		isDirty = true;
	}
}
void GameObject::removeAllGameObjectsFromMemory()
{
	const unsigned int sizeValue = gameObjectVector.size();
	for (unsigned int i = 0; i < sizeValue; i++)
		delete gameObjectVector[i];
	clearGameObjectData();
}
void GameObject::clearGameObjectData()
{
	gameObjectMap.clear();
	gameObjectVector.clear();
	objectsMarkedForDeletion.clear();
}
void GameObject::removeAllObjectsMarkedForDeletion()
{
	if (objectsMarkedForDeletion.size() <= 0)
		return;
	unsigned int deletionSize = objectsMarkedForDeletion.size();
	for (unsigned int i = 0; i < deletionSize; i++)
	{
		unsigned int gameVecObjSize = gameObjectVector.size();
		for (unsigned int j = 0; i < gameVecObjSize; j++)
		{
			if (objectsMarkedForDeletion[i] != nullptr)
			{
				if (gameObjectVector[j] == objectsMarkedForDeletion[i])
				{
					gameObjectMap.erase(objectsMarkedForDeletion[i]->getName());
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
