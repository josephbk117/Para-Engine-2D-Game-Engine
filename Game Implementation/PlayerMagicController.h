#pragma once
#include <Component.h>
#include <GameObject.h>
#include <Game.h>
#include <imgui.h>
class PlayerMagicController : public Component
{
public:
	PlayerMagicController() {};
	~PlayerMagicController() {};
	virtual void start()
	{
		activeTransform = attachedGameObject->getComponent<Transform>();
		//followInYtransform = GameObject::getGameObjectWithName("Sammy")->getComponent<Transform>();
		rotOffset = 0.0f;
		shouldDoCircleMotion = true;
	}
	virtual void update()
	{
		activeTransform->setRotation(rotOffset);
		const float deltaTime = Game::getDeltaTime();
		if (shouldDoCircleMotion)
			rotOffset += deltaTime * 3.0f;
		if (Game::isKeyPressed(Key::W))
			activeTransform->setY(activeTransform->getPosition().y + 10.0f * deltaTime);
		if (Game::isKeyPressed(Key::S))
			activeTransform->setY(activeTransform->getPosition().y - 10.0f * deltaTime);
		if (Game::isKeyPressed(Key::A))
			activeTransform->setX(activeTransform->getPosition().x - 10.0f * deltaTime);
		if (Game::isKeyPressed(Key::D))
			activeTransform->setX(activeTransform->getPosition().x + 10.0f * deltaTime);
		if (Game::isKeyPressed(Key::Q))
			shouldDoCircleMotion = true;
		if (Game::isKeyReleased(Key::Q))
			shouldDoCircleMotion = false;
		//followInYtransform->position.y = activeTransform->position.y;
	}
private:
	Transform* activeTransform = nullptr;
	Transform* followInYtransform = nullptr;
	float rotOffset = 0.0f;
	bool shouldDoCircleMotion = false;
};