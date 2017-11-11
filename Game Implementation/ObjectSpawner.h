#pragma once
#include <Component.h>
#include <Game.h>
#include <AudioManager.h>
#include <string>
#include "SuddenJolt.h"
#include "SoundSource.h"

class ObjectSpawner : public Component
{
public:
	virtual void start()
	{
		timer = 0.0f;
		count = 0;
		texId[0] = TextureManager::getTextureFromReference("texThree");
		texId[1] = TextureManager::getTextureFromReference("texTwo");
		texId[2] = TextureManager::getTextureFromReference("texOne");
		sndRef = AudioManager::getAudioFromReference("snd_1");
	}
	virtual void update()
	{
		timer += Game::getDeltaTime();
		if (count < 1000)
		{
			if (timer >= 2.8f)
			{
				float yVal = 3 + count * 0.7f;
				for (int inc = 0; inc < 3; inc++)
				{
					GameObject* tempGameObject;
					std::string name = "NewOne" + std::to_string(count) + "_" + std::to_string(inc);
					tempGameObject = GameObject::createGameObject(name);
					tempGameObject->addComponent(new Transform(glm::vec2(-3 + inc * 2, yVal), 0.0f, glm::vec2(1, 1)));
					Sprite* tempSprite;
					tempSprite = new Sprite();
					tempSprite->init(0.2f, 0.2f);
					tempSprite->setTextureID(texId[inc]);
					tempGameObject->addComponent(tempSprite);
					BoxCollider* boxCollider = new BoxCollider();
					boxCollider->init(tempGameObject->getComponent<Transform>()->getPosition(),
						glm::vec2(0.2f, 0.2f), PhysicsMaterial(1.0f, 0.6f, 0.3f), PhysicsBody::DYNAMIC);
					tempGameObject->addComponent(boxCollider);
					tempGameObject->addComponent(new SuddenJolt);
				}
				count++;
				timer = 0.0f;
				sndRef->play();
			}
		}
		//ImGui::Text("Frame rate: %f", 1.0f / Game::getDeltaTime());
	}
private:
	float timer;
	int count;
	unsigned int texId[3];
	SoundSource* sndRef;
};