#pragma once
#include <Game.h>
#include <Component.h>
class InitialSceneLogic : public Component
{
public:
	InitialSceneLogic() {};
	~InitialSceneLogic() {};
	virtual void update()
	{
		if (Game::getTimeSinceStartUp() > 4.0f)
			Game::startScene("scene1", false);
	}
};