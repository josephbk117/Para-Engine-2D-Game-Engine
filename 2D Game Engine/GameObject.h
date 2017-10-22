#pragma once
#include "Sprite.h"
#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include <GL\glew.h>
#include <Box2D\Box2D.h>
#include <vector>
#include "Box.h"
#include "ShaderProgram.h"
#include "Transform.h"
#include "Component.h"
class GameObject
{
public:
	GameObject();
	GameObject(const std::string& name, unsigned int objectID);
	void setName(const std::string & name) { this->name = name; }
	std::string getName() { return name; }
	template<class T>
	T *getComponent(void);
	void addComponent(Component *comp);
	template<class T>
	bool hasComponent(void);
	Component* getAttachedComponents(unsigned int &count) { count = components.size(); return components[0]; };
	~GameObject();
private:
	std::string name;
	unsigned int objectID;
	std::vector<Component *> components;
};

template<class T>
inline T * GameObject::getComponent(void)
{
	for (int i = 0; i < components.size(); i++)
	{
		if (typeid(*components[i]) == typeid(T))
			return (T *)components[i];
	}
	return nullptr;
}

template<class T>
inline bool GameObject::hasComponent(void)
{
	for (int i = 0; i < components.size(); i++)
	{
		if (typeid(*components[i]) == typeid(T))
			return true;
	}
	return false;
}
