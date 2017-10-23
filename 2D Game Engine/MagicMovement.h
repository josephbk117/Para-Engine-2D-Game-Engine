#pragma once
#include "Component.h"
#include "GameObject.h"
class MagicMovement : public Component
{
public:
	MagicMovement() {};
	~MagicMovement() {};
	virtual void start()
	{
		activeTransform = GameObject::getGameObjectWithName("Lola")->getComponent<Transform>();
		rotOffset = 0.0f;
	}
	virtual void update()
	{
		activeTransform->rotation = rotOffset;
		rotOffset += 0.01f;
	}
private:
	Transform* activeTransform;
	float rotOffset;
};