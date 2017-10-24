#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Game.h"
class MagicMovement : public Component
{
public:
	MagicMovement() {};
	~MagicMovement() {};
	virtual void start()
	{
		activeTransform = GameObject::getGameObjectWithName("Lola")->getComponent<Transform>();
		rotOffset = 0.0f;
		shouldDoCircleMotion = true;
	}
	virtual void update()
	{
		activeTransform->rotation = rotOffset;
		float deltaTime = Game::getDeltaTime();
		if (shouldDoCircleMotion)
		{
			activeTransform->position.x = activeTransform->position.x + (sin(rotOffset)*0.3f);
			activeTransform->position.y = activeTransform->position.y + (cos(rotOffset)*0.3f);
			rotOffset += deltaTime;
		}
		if (Game::isKeyPressed(Key::W))
			activeTransform->position.y += 100.0f * deltaTime;
		if (Game::isKeyPressed(Key::S))
			activeTransform->position.y -= 100.0f * deltaTime;
		if (Game::isKeyPressed(Key::A))
			activeTransform->position.x -= 100.0f * deltaTime;
		if (Game::isKeyPressed(Key::D))
			activeTransform->position.x += 100.0f * deltaTime;
		if (Game::isKeyPressed(Key::Q))
			shouldDoCircleMotion = true;
		if (Game::isKeyReleased(Key::Q))
			shouldDoCircleMotion = false;
	}
private:
	Transform* activeTransform;
	float rotOffset;
	bool shouldDoCircleMotion;
};