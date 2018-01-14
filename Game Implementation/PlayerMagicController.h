#pragma once
#include <Component.h>
#include <GameObject.h>
#include <Game.h>
#include <SoundSource.h>
#include <imgui.h>
class PlayerMagicController : public Component
{
public:

	virtual void start()
	{
		activeTransform = attachedGameObject->getComponent<Transform>();
		rotOffset = 0.0f;
		shouldDoCircleMotion = true;
		sndBgMusic = AudioManager::loadAudioFromFile("Test Resources\\sndtrack2.wav", "bgMusic");
		sndBgMusic->play();
		sndBgMusic->setLooping(true);
	}
	virtual void update()
	{
		activeTransform->setRotation(rotOffset);
		const float deltaTime = Game::getDeltaTime();
		if (shouldDoCircleMotion)
			rotOffset += deltaTime;
		if (Game::isKeyPressed(Key::NUM_1))
		{
			if (GameObject::getGameObjectWithName("Galoo2") != nullptr)
				GameObject::deleteGameObjectWithName("Galoo2");
		}
		if (Game::isKeyPressed(Key::NUM_2))
		{
			if (GameObject::getGameObjectWithName("Galoo1") != nullptr)
				GameObject::deleteGameObjectWithName("Galoo1");
		}
		if (Game::isKeyPressed(Key::NUM_3))
		{
			if (sndBgMusic->isPlaying())
				sndBgMusic->pause();
			else
				sndBgMusic->play();
		}
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
	float rotOffset = 0.0f;
	bool shouldDoCircleMotion = false;
	SoundSource* sndBgMusic;
};