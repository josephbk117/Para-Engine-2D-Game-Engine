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
	void setName(const std::string & name) noexcept;
	const std::string& getName()const noexcept;
	void setLayerOrder(int order) noexcept;
	const int getLayerOrder()const noexcept;
	template<class T>
	T* const getComponent(void)const noexcept;
	void addComponent(Component *comp);
	template<class T>
	bool hasComponent(void)const noexcept;
	const std::vector<Component *>& getAttachedComponents();
	static GameObject* getGameObjectWithName(const std::string& name);
	template<class T>
	static GameObject* getGameObjectWithComponent(void);
	static GameObject* createGameObject(const std::string& name, bool isUI = false);
	static const std::vector<GameObject*>& getAllGameObjects() noexcept;
	static void deleteGameObjectWithName(const std::string & name);
	static void removeAllGameObjectsFromMemory();
	static void clearGameObjectData();
	~GameObject();
private:
	std::string name;
	std::vector<Component *> components;
	int layerOrder;
	bool hasStartBeenCalled = false;
	bool isPartOfUI = false;
	static std::unordered_map<std::string, GameObject*> gameObjectMap;
	static std::vector<GameObject *> gameObjectVector;
	static bool isDirty;
	static std::vector<GameObject *> objectsMarkedForDeletion;
	static void removeAllObjectsMarkedForDeletion();
#if _DEBUG
	std::unordered_map<std::string, int> typeCountMap;
#endif
};

template<class T>
T* const GameObject::getComponent(void)const noexcept
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
bool GameObject::hasComponent(void)const noexcept
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
