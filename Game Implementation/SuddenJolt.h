#pragma once
#include <Component.h>
#include <Box.h>
#include <Game.h>
class SuddenJolt : public Component
{
public:
	virtual void start()
	{
		boxCol = attachedGameObject->getComponent<BoxCollider>();
	}
	virtual void update()
	{
		if (Game::isKeyPressed(Key::U))
			boxCol->applyForce(glm::vec2(0, 20.0f));
		if (Game::isKeyPressed(Key::J))
			boxCol->applyForce(glm::vec2(0, -20.0f));
		if (Game::isKeyPressed(Key::H))
			boxCol->applyForce(glm::vec2(-20.0f, 0.0f));
		if (Game::isKeyPressed(Key::K))
			boxCol->applyForce(glm::vec2(20.0f, 0.0f));
		if (Game::isKeyPressed(Key::L))
			boxCol->applyTorque(5.0f);
	}
private:
	BoxCollider* boxCol = nullptr;
};