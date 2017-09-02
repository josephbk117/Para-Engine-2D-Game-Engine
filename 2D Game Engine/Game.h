#pragma once
#include<GL\glew.h>
#include<GLFW\glfw3.h>
#include<Box2D\Box2D.h>
#include<iostream>
#include <vector>
#include <chrono>
#include "Box.h"
#include "Circle.h"
#include "Sprite.h"
#include "ShaderProgram.h"
#include "TextureLoader.h"
#include "Camera.h"

class Game
{
public:
	Game(unsigned int screenWidth, unsigned int screenHeight, std::string title);
	void update(void(*updateFunc)());
	void processInput(GLFWwindow *window);
	Camera camera;

	~Game();
private: GLFWwindow* window;
		 std::unique_ptr<b2World> world;
		 static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		 std::vector<Box> boxes;
		 std::vector<Circle> circles;
		 std::chrono::steady_clock clockTime;
};

