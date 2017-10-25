#pragma once
class Component;
#include "GameObject.h"
class Component
{
public:
	virtual void start() { };
	virtual void update() { };
	Component() {};
	GameObject* attachedGameObject;
	virtual ~Component() {};
};