#include "Game.h"
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include <random>
#include "stb_image_write.h"
//Reuires screen width, screen height and title of window
Game::Game(unsigned int screenWidth, unsigned int screenHeight, std::string title)
{
	world = std::make_unique<b2World>(b2Vec2(0, -9.81f));
	std::mt19937 randGenerator;

	std::uniform_real_distribution<float> x1Pos(-400, 400);
	std::uniform_real_distribution<float> y1Pos(-420, 420);

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
	// Setup ImGui binding
	IMGUI_INIT(window, true);
	GameObject* tempGameObject;

	unsigned int texVal1 = TextureLoader::loadTextureFromFile("Test Resources\\frasa.png", false);
	unsigned int texVal2 = TextureLoader::loadTextureFromFile("Test Resources\\mamma.png", false);
	

	tempGameObject = new GameObject(world.get(), glm::vec2(0, 400),
		glm::vec2(50, 50), b2BodyType::b2_dynamicBody, 1.0);
	tempGameObject->setName("Sama Baba");
	tempGameObject->setTextureID(texVal1);
	gameObjects.push_back(tempGameObject);

	tempGameObject = new GameObject(world.get(), glm::vec2(20, 300),
		glm::vec2(50, 50), b2BodyType::b2_dynamicBody, 1.0);
	tempGameObject->setName("Loco baoco");
	tempGameObject->setTextureID(texVal1);
	gameObjects.push_back(tempGameObject);

	tempGameObject = new GameObject(world.get(), glm::vec2(-10, 250),
		glm::vec2(50, 50), b2BodyType::b2_dynamicBody, 1.0);
	tempGameObject->setName("Gaga Googoo");
	tempGameObject->setTextureID(texVal1);

	gameObjects.push_back(tempGameObject);

	tempGameObject = new GameObject(world.get(), glm::vec2(0, 0),
		glm::vec2(250, 50), b2BodyType::b2_staticBody, 0);
	tempGameObject->setName("Jaja Kacha");
	tempGameObject->setTextureID(texVal2);

	gameObjects.push_back(tempGameObject);
	tempGameObject = new GameObject(world.get(), glm::vec2(150, 200),
		glm::vec2(250, 50), b2BodyType::b2_staticBody, 0);
	tempGameObject->setTextureID(texVal2);

	gameObjects.push_back(tempGameObject);

}
ImVec4 clearColour;
//Pass in a function to be run every frame
void Game::update(void(*updateFunc)())
{
	camera.init(glm::vec2(600, 600));
	camera.setPosition(glm::vec2(0, 0));

	ShaderProgram shaderProgram;
	shaderProgram.compileShaders("Test Resources\\spriteBase.vs", "Test Resources\\spriteBase.fs");
	shaderProgram.addAttribute("vertexPosition");
	shaderProgram.linkShaders();

	GLint textureLocation = shaderProgram.getUniformLocation("textureOne");
	GLint uniformProjectionMatrixLocation = shaderProgram.getUniformLocation("projection");

	Sprite bgSprite;
	bgSprite.init(-200, -200, 800, 700);
	unsigned int texVal3 = TextureLoader::loadTextureFromFile("Test Resources\\lili.jpg", false);
	while (!glfwWindowShouldClose(window))
	{
		IMGUI_NEWFRAME();
		std::chrono::steady_clock::time_point start = clockTime.now();
		glClear(GL_COLOR_BUFFER_BIT);
		processInput(window);
		camera.update();
		//updateFunc();	

		for (unsigned int i = 0; i < gameObjects.size(); i++)
		{
			ImGui::Text("OBJECT : %s is at position = ( %.2f , %.2f )", gameObjects[i]->getName().c_str(),
				gameObjects[i]->getPosition().x, gameObjects[i]->getPosition().y);
		}
		ImGui::ColorEdit3("BG COLOUR", (float*)&clearColour);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		glClearColor(clearColour.x, clearColour.y, clearColour.z, 1.0f);

		std::chrono::duration<float> frameTime = clockTime.now() - start;
		world->Step(frameTime.count() * 10, 5, 6);
		shaderProgram.use();
		
		glm::mat4 cameraMatrix = camera.getOrthoMatrix();
		glUniformMatrix4fv(uniformProjectionMatrixLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
		glUniform1i(textureLocation, 0);
		bgSprite.setTextureID(texVal3);
		bgSprite.draw();
		for (unsigned int i = 0; i < gameObjects.size(); i++)
			gameObjects[i]->drawObject(shaderProgram);
		
		shaderProgram.unuse();
		glBindTexture(GL_TEXTURE_2D, 0);
		ImGui::Render();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	IMGUI_SHUTDOWN();
	glfwTerminate();
	return;
}
bool pressed = false;
void Game::processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		gameObjects[0]->setObjectVelocity(0.0f, 50.0f);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		gameObjects[0]->setObjectVelocity(0.0f, -50.0f);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		gameObjects[0]->setObjectVelocity(-50.0f, 0.0);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		gameObjects[0]->setObjectVelocity(50.0f, 0.0);
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		gameObjects[0]->setAngularVelocity(-10.0f);
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		gameObjects[0]->setAngularVelocity(10.0f);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		camera.setPosition(camera.getPosition() + glm::vec2(0, 1.0f));
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		camera.setPosition(camera.getPosition() + glm::vec2(0, -1.0f));
	else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		camera.setPosition(camera.getPosition() + glm::vec2(-1.0f, 0));
	else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		camera.setPosition(camera.getPosition() + glm::vec2(1.0f, 0));

}

Game::~Game()
{
}

void Game::framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}
