#pragma once
#include <vector>
#include <algorithm>
#include <unordered_map>
class GameObject;
#include "Component.h"

class GameObject
{
	friend class Game;
public:
	GameObject();
	GameObject(const std::string& name);
	void setName(const std::string & name) { isDirty = true; this->name = name; }
	const std::string& getName()const { return name; }
	void setLayerOrder(int order) { isDirty = true; this->layerOrder = order; }
	const int& getLayerOrder()const { return layerOrder; }
	template<class T>
	T* const getComponent(void)const;
	void addComponent(Component *comp);
	template<class T>
	bool hasComponent(void)const;
	const std::vector<Component *>& getAttachedComponents() { return components; };
	static GameObject* getGameObjectWithName(const std::string& name)
	{
		return gameObjectMap[name];
	}
	template<class T>
	static GameObject* getGameObjectWithComponent(void);
	static GameObject* createGameObject(const std::string& name)
	{
		isDirty = true;
		GameObject* gameObject = new GameObject(name);
		gameObjectMap[name] = gameObject;
		gameObjectVector.push_back(gameObject);
		return gameObject;
	}
	static const std::vector<GameObject*>& getAllGameObjects()
	{
		return gameObjectVector;
	}
	static void deleteGameObjectWithName(const std::string & name)
	{
		if (gameObjectMap.count(name) <= 0)
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
	static void removeAllGameObjectsFromMemory()
	{
		const unsigned int sizeValue = gameObjectVector.size();
		for (unsigned int i = 0; i < sizeValue; i++)
			delete gameObjectVector[i];
		clearGameObjectData();
	}
	static void clearGameObjectData()
	{
		gameObjectMap.clear();
		gameObjectVector.clear();
		objectsMarkedForDeletion.clear();
	}
	~GameObject();
private:
	std::string name;
	std::vector<Component *> components;
	int layerOrder;
	bool hasStartBeenCalled = false;
	static std::unordered_map<std::string, GameObject*> gameObjectMap;
	static std::vector<GameObject *> gameObjectVector;
	static bool isDirty;
	static std::vector<GameObject *> objectsMarkedForDeletion;
	static void removeAllObjectsMarkedForDeletion();
};

template<class T>
T* const GameObject::getComponent(void)const
{
	const unsigned int sizeValue = components.size();
	for (unsigned int i = 0; i < sizeValue; i++)
	{
		if (typeid(*components[i]) == typeid(T))
			return (T *)components[i];
	}
	return nullptr;
}

template<class T>
bool GameObject::hasComponent(void)const
{
	const unsigned int sizeValue = components.size();
	for (unsigned int i = 0; i < sizeValue; i++)
	{
		if (typeid(*components[i]) == typeid(T))
			return true;
	}
	return false;
}

template<class T>
GameObject * GameObject::getGameObjectWithComponent(void)
{
	const unsigned int sizeValue = gameObjectVector.size();
	for (unsigned int i = 0; i < sizeValue; i++)
	{
		if (gameObjectVector[i]->hasComponent<T>())
			return gameObjectVector[i];
	}
	return nullptr;
}
