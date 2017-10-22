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
	void update(void(*updateFunc)());
	void processInput(GLFWwindow *window);
	Camera camera;
	GameObject* findGameObjectWithName(const std::string& name);
	~Game();
private:
	GLFWwindow* window;
	std::unique_ptr<b2World> world;
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	std::chrono::steady_clock clockTime;
	std::vector<GameObject*> gameObjects;
};

