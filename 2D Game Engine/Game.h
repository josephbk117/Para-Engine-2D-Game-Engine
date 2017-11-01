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
	Game(unsigned int screenWidth, unsigned int screenHeight, std::string title);
	void initialize();
	void update();
	void setCursor(const std::string & cursorImagePath);
	void hideCursor(bool hide);
	void lockCursor(bool lock);
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
	Camera* camera;
	~Game();
private:
	std::vector<GameObject *> gameObjects;
	static std::unique_ptr<b2World> world;
	static std::thread* audioThread;
	static bool frameBufferSizeUpated;
	static float deltaTime;
	static float timeSinceStartUp;
	static glm::vec2 mouseCoord;
	struct InternalAcess;
	static InternalAcess* acess;
};


