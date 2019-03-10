#pragma once
#include <ParaEngine/Game.h>
#include <ParaEngine/Component.h>
class InitialSceneLogic : public Component
{
public:

	virtual void update()
	{
		if (Game::getTimeSinceStartUp() > 4.0f)
			Game::startScene("scene1", false);
	}
};