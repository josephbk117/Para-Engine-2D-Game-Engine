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
		if (Game::isKeyPressed(Key::L))
			boxCol->getBody()->ApplyTorque(700000.0f, true);
	}
private:
	BoxCollider* boxCol;
};