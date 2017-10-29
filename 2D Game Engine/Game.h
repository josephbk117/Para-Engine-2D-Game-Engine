#pragma once
class b2World;
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <GLM\glm.hpp>
#include <memory>
#include <chrono>
#include "GameObject.h"
#include "InputData.h"
#include "Camera.h"

class Game
{
public:
	Game(unsigned int screenWidth, unsigned int screenHeight, std::string title);
	void initialize();
	void update();
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
	std::chrono::steady_clock clockTime;
	std::vector<GameObject *> gameObjects;
	static GLFWwindow* window;
	static std::unique_ptr<b2World> world;
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static bool frameBufferSizeUpated;
	static float deltaTime;
	static float timeSinceStartUp;
	static glm::vec2 mouseCoord;
};


