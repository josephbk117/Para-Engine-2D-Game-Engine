#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Game.h"
#include <iomanip>
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
		activeTransform->position.x = activeTransform->position.x + (sin(rotOffset)*0.35f);
		activeTransform->position.y = activeTransform->position.y + (cos(rotOffset)*0.35f);
		rotOffset += Game::getDeltaTime();
	}
private:
	Transform* activeTransform;
	float rotOffset;
};