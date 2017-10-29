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
		followInYtransform = GameObject::getGameObjectWithName("Sammy")->getComponent<Transform>();
		rotOffset = 0.0f;
		shouldDoCircleMotion = true;
	}
	virtual void update()
	{
		activeTransform->rotation = rotOffset;
		float deltaTime = Game::getDeltaTime();
		if (shouldDoCircleMotion)
		{
			activeTransform->position.x = activeTransform->position.x + (glm::sin(rotOffset) * 0.01f);
			activeTransform->position.y = activeTransform->position.y + (glm::cos(rotOffset) * 0.01f);
			rotOffset += deltaTime * 3.0f;
		}
		if (Game::isKeyPressed(Key::W))
			activeTransform->position.y += 10.0f * deltaTime;
		if (Game::isKeyPressed(Key::S))
			activeTransform->position.y -= 10.0f * deltaTime;
		if (Game::isKeyPressed(Key::A))
			activeTransform->position.x -= 10.0f * deltaTime;
		if (Game::isKeyPressed(Key::D))
			activeTransform->position.x += 10.0f * deltaTime;
		if (Game::isKeyPressed(Key::Q))
			shouldDoCircleMotion = true;
		if (Game::isKeyReleased(Key::Q))
			shouldDoCircleMotion = false;
		followInYtransform->position.y = activeTransform->position.y;

	}
private:
	Transform* activeTransform = nullptr;
	Transform* followInYtransform = nullptr;
	float rotOffset;
	bool shouldDoCircleMotion;
};