#pragma once
class Component;
#include "GameObject.h"
class Component
{
public:
	virtual void start() { };
	virtual void update() { };
	virtual void collisionStarted(GameObject* gameObject) { };
	virtual void collisionEnded(GameObject* gameObject) { };
	GameObject* attachedGameObject = nullptr;
};