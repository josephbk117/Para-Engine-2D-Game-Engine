#pragma once
#include <Component.h>
#include <Transform.h>
#include <Game.h>
class MagicObjectScaler : public Component
{
public:
	virtual void start()
	{
		transform = attachedGameObject->getComponent<Transform>();
	}
	virtual void update()
	{
		transform->scale = glm::vec2(1.0f + abs(sin(Game::getTimeSinceStartUp()*10.0f)), 1.0f);
		transform->position = Game::camera->convertScreenPointToWorldPoint(glm::vec2(Game::getMouseCoords()->x, Game::getMouseCoords()->y), Game::getWindowSize());
	}

private:
	Transform* transform = nullptr;
};