#pragma once
#include <ParaEngine/Component.h>
#include <ParaEngine/Game.h>
#include <ParaEngine/AudioManager.h>
#include <string>
#include "SuddenJolt.h"
#include <ParaEngine/SoundSource.h>

class ObjectSpawner : public Component
{
public:
	virtual void start()
	{
		timer = 0.0f;
		count = 0;
		texId[0] = TextureManager::getTextureIdFromReference("texThree");
		texId[1] = TextureManager::getTextureIdFromReference("texTwo");
		texId[2] = TextureManager::getTextureIdFromReference("texOne");
		sndRef = AudioManager::getAudioFromReference("snd_1");
	}
	virtual void update()
	{
		timer += Game::getDeltaTime();
		if (count < 10)
		{
			if (timer >= 1.0f)
			{
				GameObject* tempGameObject = nullptr;
				float yVal = 3 + count * 0.7f;
				for (int inc = 0; inc < 20; inc++)
				{
					std::string name = "New One_" + std::to_string(count) + "_" + std::to_string(inc);
					tempGameObject = GameObject::createGameObject(name);
					tempGameObject->getComponent<Transform>()->setPosition(glm::vec2(-3 + inc * 0.3f, yVal));

					Sprite* tempSprite;
					tempSprite = new Sprite();
					tempSprite->init(0.2f, 0.2f);
					tempSprite->setTextureID(texId[inc % 3]);
					tempGameObject->addComponent(tempSprite);
					BoxCollider* boxCollider = new BoxCollider();
					boxCollider->init(tempGameObject->getComponent<Transform>()->getPosition(),
						glm::vec2(0.2f, 0.2f), PhysicsMaterial(0, 0, 1.0f, 0.6f, 0.3f), PhysicsBody::DYNAMIC);
					tempGameObject->addComponent(boxCollider);
					tempGameObject->addComponent(new SuddenJolt);
				}
				count++;
				timer = 0.0f;
				sndRef->play();
			}
		}
	}
private:
	float timer = 0.0f;
	int count;
	unsigned int texId[3];
	SoundSource* sndRef = nullptr;
};