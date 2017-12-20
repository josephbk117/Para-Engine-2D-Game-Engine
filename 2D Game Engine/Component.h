#pragma once
class Component;
#include "GameObject.h"
class Component
{
public:
	virtual void start() { };
	virtual void update() { };
	virtual void collisionStarted(GameObject* gameObject) noexcept { };
	virtual void collisionEnded(GameObject* gameObject) noexcept { };
	GameObject* attachedGameObject = nullptr;
};