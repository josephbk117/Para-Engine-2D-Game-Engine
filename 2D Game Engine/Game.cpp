#include "Game.h"
#include <random>

Game::Game(unsigned int screenWidth, unsigned int screenHeight, std::string title)
{
	world = std::make_unique<b2World>(b2Vec2(0, -9.81));
	//Ground
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, -80);
	b2Body* groundBody = world->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(80, 10);
	groundBody->CreateFixture(&groundBox, 0);

	std::mt19937 randGenerator;
	std::uniform_real_distribution<float> xPos(-60, 60);
	std::uniform_real_distribution<float> yPos(10, 80);

	const int NUM_BOXES = 120;
	for (int i = 0; i < NUM_BOXES; i++)
	{
		Box box;
		//world.get cus of unique pointer
		box.init(world.get(), glm::vec2(xPos(randGenerator), yPos(randGenerator)), glm::vec2(6, 6));
		boxes.push_back(box);
	}

	glfwInit();
	window = glfwCreateWindow(screenWidth, screenHeight, title.c_str(), NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	GLenum err = glewInit();
	if (GLEW_OK != err)
		std::cout << "Error: %s\n" << glewGetErrorString(err);
	else
		std::cout << " Glew initialsed" << std::endl;
}

void Game::update(void(*updateFunc)())
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100, 100, -100, 100, 0.1, -10);
	glMatrixMode(GL_MODELVIEW);
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		processInput(window);
		//updateFunc();
		for (int i = 0; i < boxes.size(); i++)
		{
			glm::vec4 destRect;
			destRect.x = boxes[i].getBody()->GetPosition().x;
			destRect.y = boxes[i].getBody()->GetPosition().y;
			destRect.z = boxes[i].getDimensions().x;
			destRect.w = boxes[i].getDimensions().y;			

			glBegin(GL_QUADS);
			glVertex2f(destRect.x, destRect.y);
			glVertex2f(destRect.x + destRect.z, destRect.y);
			glVertex2f(destRect.x + destRect.z, destRect.y + destRect.w);
			glVertex2f(destRect.x, destRect.y + destRect.w);
			glEnd();
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
		world->Step(1.0 / 100.0, 5, 6);
	}
	glfwTerminate();
	return;
}

void Game::processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		world->SetGravity(b2Vec2(0, 9.81));
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		world->SetGravity(b2Vec2(0, -9.81));
}

Game::~Game()
{
}

void Game::framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100, 100, -100, 100, 0.1, -10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
