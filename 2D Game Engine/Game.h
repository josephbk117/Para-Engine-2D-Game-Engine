#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <Box2D\Box2D.h>
#include <iostream>
#include <vector>
#include <chrono>
#include "Box.h"
#include "Sprite.h"
#include "ShaderProgram.h"
#include "TextureLoader.h"
#include "Camera.h"
#include "GameObject.h"

class Game
{
public:
	Game(unsigned int screenWidth, unsigned int screenHeight, std::string title);
	//void initialize(std::vector<void(*)()>);
	void initialize();
	//void update(void(*updateFunc)());
	void update();
	void processInput(GLFWwindow *window);
	b2World* getPhysicsWorld()
	{
		return world.get();
	}
	Camera camera;
	~Game();
private:
	GLFWwindow* window;
	std::unique_ptr<b2World> world;
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static bool frameBufferSizeUpated;
	std::chrono::steady_clock clockTime;
	std::vector<GameObject*> gameObjects;
};

