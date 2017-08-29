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
	std::uniform_real_distribution<float> yPos(10, 120);

	const int NUM_BOXES = 10, NUM_CIRCLES = 10;
	for (int i = 0; i < NUM_BOXES; i++)
	{
		Box box;
		//world.get cus of unique pointer
		box.init(world.get(), glm::vec2(xPos(randGenerator), yPos(randGenerator)), glm::vec2(6, 6));
		boxes.push_back(box);
	}
	for (int i = 0; i < NUM_CIRCLES; i++)
	{
		Circle circle;
		//world.get cus of unique pointer
		circle.init(world.get(), glm::vec2(xPos(randGenerator), yPos(randGenerator)), 4);
		circles.push_back(circle);
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
	//glLoadIdentity();
	//glOrtho(-100, 100, -100, 100, 0.1, -10);
	//glMatrixMode(GL_MODELVIEW);
	Sprite sprite, sprite2, sprite3;
	sprite.init(0, 0, 0.5, 0.5);
	sprite2.init(-0.5, 0, 0.4, 0.4);
	sprite3.init(-0.5, 0.5, 0.3, 0.3);
	ShaderProgram shaderProgram;
	shaderProgram.compileShaders("F:\\Visual Studio 2017\\Projects\\2D Game Engine\\Debug\\spriteBase.vs", "F:\\Visual Studio 2017\\Projects\\2D Game Engine\\Debug\\spriteBase.fs");
	shaderProgram.addAttribute("vertexPosition");
	shaderProgram.linkShaders();
	unsigned int texVal1 = TextureLoader::loadTextureFromFile("F:\\Visual Studio 2017\\Projects\\2D Game Engine\\Debug\\asteroid.png", false);
	while (!glfwWindowShouldClose(window))
	{
		std::chrono::steady_clock::time_point start = clockTime.now();
		glClear(GL_COLOR_BUFFER_BIT);
		processInput(window);
		//updateFunc();
		/*for (int i = 0; i < boxes.size(); i++)
			boxes[i].draw();
		for (int i = 0; i < circles.size(); i++)
			circles[i].draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
		std::chrono::duration<float> frameTime = clockTime.now() - start;
		world->Step(frameTime.count()*10.0, 5, 6);*/
		shaderProgram.use();
		glBindTexture(GL_TEXTURE_2D, texVal1);
		GLint textureLocation = shaderProgram.getUniformLocation("textureOne");
		glUniform1i(textureLocation, 0);
		sprite.draw();
		sprite2.draw();
		sprite3.draw();
		shaderProgram.unuse();
		glBindTexture(GL_TEXTURE_2D, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
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
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		for (int i = 0; i < circles.size(); i++)
			circles[i].getBody()->ApplyForce(b2Vec2(0, 1500), circles[i].getBody()->GetPosition(), true);
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		for (int i = 0; i < boxes.size(); i++)
			boxes[i].getBody()->ApplyForce(b2Vec2(0, 800), boxes[i].getBody()->GetPosition(), true);
	}
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
