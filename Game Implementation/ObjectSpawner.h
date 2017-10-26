#pragma once
#include <Component.h>
#include <Game.h>
class ObjectSpawner : public Component
{
public:
	virtual void start()
	{
		timer = 0.0f;
		count = 0;
		texId = GameObject::getGameObjectWithName("Babu")->getComponent<Sprite>()->getTextureID();
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
				tempSprite->setTextureID(texId);
				tempGameObject->addComponent(tempSprite);
				BoxCollider* boxCollider = new BoxCollider();
				boxCollider->init(tempGameObject->getComponent<Transform>()->position,
					glm::vec2(40, 40), PhysicsBody::DYNAMIC, 1.0f);
				tempGameObject->addComponent(boxCollider);
				count++;
				timer = 0.0f;
			}
		}
	}
private:
	float timer;
	int count;
	unsigned int texId;
};