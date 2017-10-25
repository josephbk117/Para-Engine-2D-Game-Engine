#include "Game.h"
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include <random>
#include <typeinfo>
#include "stb_image_write.h"

bool Game::frameBufferSizeUpated;
float Game::deltaTime;
float Game::timeSinceStartUp;
std::unique_ptr<b2World> Game::world;
GLFWwindow* Game::window;
glm::vec2 Game::mouseCoord;
Game::Game(unsigned int screenWidth, unsigned int screenHeight, std::string title)
{
	world = std::make_unique<b2World>(b2Vec2(0, -9.81f));
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
	IMGUI_INIT(window, true);

	camera.init(glm::vec2(600, 600));
	camera.setPosition(glm::vec2(0, 0));
}
void Game::initialize()
{
	gameObjects = GameObject::getAllGameObjects();
	for (int i = 0; i < gameObjects.size(); i++)
	{
		std::vector<Component*> componentsAttachedToObject =
			GameObject::getGameObjectWithName(gameObjects[i]->getName())->getAttachedComponents();
		for (int i = 0; i < componentsAttachedToObject.size(); i++)
			(*componentsAttachedToObject[i]).start();
	}
	std::stable_sort(gameObjects.begin(), gameObjects.end(), [](GameObject* a, GameObject* b)
	{return a->getLayerOrder() < b->getLayerOrder(); });
}
ImVec4 clearColour;
void Game::update()
{
	ShaderProgram shaderProgram;
	shaderProgram.compileShaders("Test Resources\\spriteBase.vs", "Test Resources\\spriteBase.fs");
	shaderProgram.addAttribute("vertexPosition");
	shaderProgram.linkShaders();

	GLint textureLocation = shaderProgram.getUniformLocation("textureOne");
	GLint uniformProjectionMatrixLocation = shaderProgram.getUniformLocation("projection");
	GLint uniformModelMatrixLocation = shaderProgram.getUniformLocation("model");

	std::chrono::steady_clock::time_point start = clockTime.now();
	std::chrono::steady_clock::time_point initialTime = clockTime.now();
	deltaTime = 0.0f;
	timeSinceStartUp = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		if (frameBufferSizeUpated)
		{
			int width, height;
			glfwGetWindowSize(window, &width, &height);
			std::cout << "\nUpdated to : " << width << " ," << height;
			camera.setScreenRatio(vec2(width, height));
			frameBufferSizeUpated = false;
		}
		IMGUI_NEWFRAME();

		glClear(GL_COLOR_BUFFER_BIT);
		processInput(window);
		camera.update();

		/*for (unsigned int i = 0; i < gameObjects.size(); i++)
		{
			Transform * temp = gameObjects[i]->getComponent<Transform>();
			ImGui::Text("OBJECT : %s is at position = ( %.2f , %.2f ) | Rotation is : %.2f", gameObjects[i]->getName().c_str(),
				temp->position.x, temp->position.y, temp->rotation);
		}
		ImGui::ColorEdit3("BG COLOUR", (float*)&clearColour);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);*/

		glClearColor(clearColour.x, clearColour.y, clearColour.z, 1.0f);

		shaderProgram.use();
		glm::mat4 matrixTransform;
		glm::mat4 cameraMatrix = camera.getOrthoMatrix();
		glUniformMatrix4fv(uniformProjectionMatrixLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
		glUniform1i(textureLocation, 0);

		for (int i = 0; i < gameObjects.size(); i++)
		{
			std::vector<Component*> componentsAttachedToObject =
				GameObject::getGameObjectWithName(gameObjects[i]->getName())->getAttachedComponents();
			for (int i = 0; i < componentsAttachedToObject.size(); i++)
				(*componentsAttachedToObject[i]).update();
		}

		for (unsigned int i = 0; i < gameObjects.size(); i++)
		{
			matrixTransform = glm::mat4(1.0f);
			if (gameObjects[i]->hasComponent<Box>())
			{
				gameObjects[i]->getComponent<Transform>()->position = glm::vec2(gameObjects[i]->getComponent<Box>()->getBody()->GetPosition().x,
					gameObjects[i]->getComponent<Box>()->getBody()->GetPosition().y);
				gameObjects[i]->getComponent<Transform>()->rotation = gameObjects[i]->getComponent<Box>()->getBody()->GetAngle();
			}

			matrixTransform = glm::translate(matrixTransform, glm::vec3(gameObjects[i]->getComponent<Transform>()->position.x,
				gameObjects[i]->getComponent<Transform>()->position.y, 0));
			matrixTransform = glm::rotate(matrixTransform, gameObjects[i]->getComponent<Transform>()->rotation, glm::vec3(0, 0, 1.0f));

			glUniformMatrix4fv(uniformModelMatrixLocation, 1, GL_FALSE, &(matrixTransform[0][0]));
			if (gameObjects[i]->hasComponent<Sprite>())
				gameObjects[i]->getComponent<Sprite>()->draw();
		}
		//TODO:
		//Make all components have reference to it's attached gameObject
		//Make transform component automatically take care of it's physics
		//Update func of transform does the matrix stuff
		//Sprite should have it's update as draw
		//Maybe each sprite should have reference to it's transform( or modelMatrixLocation and shader used)
		shaderProgram.unuse();
		glBindTexture(GL_TEXTURE_2D, 0);
		ImGui::Render();
		glfwSwapBuffers(window);
		glfwPollEvents();

		std::chrono::duration<float> frameTime = clockTime.now() - start;
		deltaTime = frameTime.count();
		world->Step(deltaTime * 5.0f, 4, 5);
		std::chrono::duration<float> sinceStart = clockTime.now() - initialTime;
		timeSinceStartUp = sinceStart.count();

		start = clockTime.now();
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
	frameBufferSizeUpated = true;
}
bool Game::isKeyPressed(Key key)
{
	if (glfwGetKey(window, (int)key) == GLFW_PRESS)
		return true;
	return false;
}
bool Game::isKeyReleased(Key key)
{
	if (glfwGetKey(window, (int)key) == GLFW_RELEASE)
		return true;
	return false;
}
const glm::vec2* Game::getMouseCoords()
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	mouseCoord.x = x;
	mouseCoord.y = y;
	return &mouseCoord;
}
b2World* Game::getPhysicsWorld()
{
	return world.get();
}
