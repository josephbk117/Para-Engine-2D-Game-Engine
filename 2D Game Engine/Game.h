#pragma once
class b2World;
#include <GLM\glm.hpp>
#include <memory>
#include <thread>
#include "GameObject.h"
#include "InputData.h"
#include "Camera.h"

class Game
{
public:
	//Game(unsigned int screenWidth, unsigned int screenHeight, std::string title);
	static void setUpEngine(unsigned int screenWidth, unsigned int screenHeight, std::string title);
	static void initialize();
	static void update();
	static void setCursor(const std::string & cursorImagePath);
	static void hideCursor(bool hide);
	static void lockCursor(bool lock);
	static bool isKeyPressed(Key key);
	static bool isKeyReleased(Key key);
	static const glm::vec2 * getMouseCoords();
	static b2World* getPhysicsWorld();
	static float getDeltaTime()
	{
		return deltaTime;
	}
	static float getTimeSinceStartUp()
	{
		return timeSinceStartUp;
	}
	static void cleanUp();
	static Camera* camera;
private:
	static std::vector<GameObject *> gameObjects;
	static std::unique_ptr<b2World> world;
	static bool frameBufferSizeUpated;
	static float deltaTime;
	static float timeSinceStartUp;
	static glm::vec2 mouseCoord;
	struct InternalAcess;
	static InternalAcess* acess;
};


