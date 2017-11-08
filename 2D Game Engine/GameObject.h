#pragma once
#include <vector>
#include <unordered_map>
class GameObject;
#include "Component.h"

class GameObject
{
public:
	GameObject();
	GameObject(const std::string& name);
	void setName(const std::string & name) { this->name = name; }
	std::string getName()const { return name; }
	void setLayerOrder(int order) { this->layerOrder = order; }
	int getLayerOrder()const { return layerOrder; }
	template<class T>
	T *getComponent(void);
	void addComponent(Component *comp);
	template<class T>
	bool hasComponent(void);
	std::vector<Component *> getAttachedComponents() { return components; };
	static GameObject* getGameObjectWithName(const std::string& name)
	{
		return gameObjectMap[name];
	}
	template<class T>
	static GameObject* getGameObjectWithComponent(void);
	static GameObject* createGameObject(const std::string& name)
	{
		GameObject* gameObject = new GameObject(name);
		gameObjectMap[name] = gameObject;
		gameObjectVector.push_back(gameObject);
		return gameObject;
	}
	static std::vector<GameObject*> getAllGameObjects()
	{
		return gameObjectVector;
	}
	static void removeAllGameObjectsFromMemory()
	{
		for (unsigned int i = 0; i < gameObjectVector.size(); i++)
			delete gameObjectVector[i];
	}
	~GameObject();
private:
	std::string name;
	std::vector<Component *> components;
	int layerOrder;
	static std::unordered_map<std::string, GameObject*> gameObjectMap;
	static std::vector<GameObject *> gameObjectVector;
};

template<class T>
inline T * GameObject::getComponent(void)
{
	unsigned int sizeValue = components.size();
	for (unsigned int i = 0; i < sizeValue; i++)
	{
		if (typeid(*components[i]) == typeid(T))
			return (T *)components[i];
	}
	return nullptr;
}

template<class T>
inline bool GameObject::hasComponent(void)
{
	unsigned int sizeValue = components.size();
	for (unsigned int i = 0; i < sizeValue; i++)
	{
		if (typeid(*components[i]) == typeid(T))
			return true;
	}
	return false;
}

template<class T>
inline GameObject * GameObject::getGameObjectWithComponent(void)
{
	unsigned int sizeValue = gameObjectVector.size();
	for (int i = 0; i < sizeValue; i++)
	{
		if (gameObjectVector[i]->hasComponent<T>())
			return gameObjectVector[i];
	}
	return nullptr;
}
