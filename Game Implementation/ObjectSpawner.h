#pragma once
#include <Component.h>
#include <Game.h>
#include "SuddenJolt.h"
#include <AudioManager.h>
class ObjectSpawner : public Component
{
public:
	virtual void start()
	{
		timer = 0.0f;
		count = 0;
		texId[0] = TextureLoader::getTextureFromReference("texThree");
		texId[1] = TextureLoader::getTextureFromReference("texTwo");
		texId[2] = TextureLoader::getTextureFromReference("texOne");
		sndRef.create("F:\\Visual Studio 2017\\Projects\\2D Game Engine\\Debug\\Test Resources\\Swoosh.wav").play();
	}
	virtual void update()
	{
		timer += Game::getDeltaTime();
		if (count < 12)
		{
			if (timer >= 1.0f)
			{
				GameObject* tempGameObject;
				tempGameObject = GameObject::createGameObject("NewOne" + std::to_string(count));
				tempGameObject->addComponent(new Transform(glm::vec2(-120, 0 + count * 40), 0.0f, glm::vec2(1, 1)));
				Sprite* tempSprite;
				tempSprite = new Sprite();
				tempSprite->init(40, 40);
				tempSprite->setTextureID(texId[count%3]);
				tempGameObject->addComponent(tempSprite);
				BoxCollider* boxCollider = new BoxCollider();
				boxCollider->init(tempGameObject->getComponent<Transform>()->position,
					glm::vec2(40, 40), PhysicsBody::DYNAMIC, 1.0f);
				tempGameObject->addComponent(boxCollider);
				tempGameObject->addComponent(new SuddenJolt);
				count++;
				timer = 0.0f;
				sndRef.play();
			}
		}
		ImGui::Text("Frame rate: %f", 1.0f / Game::getDeltaTime());
	}
private:
	float timer;
	int count;
	unsigned int texId[3];
	YSE::sound sndRef;
	
};