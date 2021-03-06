#pragma once
#include <ParaEngine/Component.h>
#include <ParaEngine/Box.h>
#include <ParaEngine/Game.h>
#include <iostream>

class SuddenJolt : public Component
{
public:
	virtual void start()
	{
		boxCol = attachedGameObject->getComponent<BoxCollider>();
		physicsMover = GameObject::getGameObjectWithName("PhyMove")->getComponent<BoxCollider>();
	}
	virtual void update()
	{
		if (Game::isKeyPressed(Key::U))
			boxCol->applyForce(glm::vec2(0, 20.0f));
		if (Game::isKeyPressed(Key::J))
			boxCol->applyForce(glm::vec2(0, -200.0f));
		if (Game::isKeyPressed(Key::H))
			boxCol->applyForce(glm::vec2(-80.0f, 0.0f));
		if (Game::isKeyPressed(Key::K))
			boxCol->applyForce(glm::vec2(80.0f, 0.0f));
		if (Game::isKeyPressed(Key::L))
			boxCol->applyTorque(5.0f);
		if (Game::isKeyPressed(Key::N))
			physicsMover->setPosition(glm::vec2(physicsMover->getPosition().x + 0.1*Game::getDeltaTime(), physicsMover->getPosition().y));
		if (Game::isKeyPressed(Key::V))
			physicsMover->setPosition(glm::vec2(physicsMover->getPosition().x - 0.1*Game::getDeltaTime(), physicsMover->getPosition().y));
		if (Game::isKeyPressed(Key::G))
			physicsMover->setPosition(glm::vec2(physicsMover->getPosition().x, physicsMover->getPosition().y + 0.1*Game::getDeltaTime()));
		if (Game::isKeyPressed(Key::B))
			physicsMover->setPosition(glm::vec2(physicsMover->getPosition().x, physicsMover->getPosition().y - 0.1*Game::getDeltaTime()));

	}
	virtual void collisionStarted(GameObject* gameObject)
	{
		++collisionCount;
		boxCol->applyTorque(3.0f);
		if (collisionCount >= 40)
			GameObject::deleteGameObjectWithName(attachedGameObject->getName());
	}
	virtual void collisionEnded(GameObject* gameObject)
	{
		boxCol->applyTorque(-4.0f);
	}
private:
	BoxCollider* boxCol = nullptr;
	BoxCollider* physicsMover = nullptr;
	int collisionCount = 0;
};