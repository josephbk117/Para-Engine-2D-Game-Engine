#include <GL\glew.h>
#include "Game.h"
#include <iostream>
#include <vector>
#include <random>
#include <typeinfo>
#include <Yse\yse.hpp>
#include <Box2D\Box2D.h>
#include <memory>
#include <chrono>
//#include "imgui.h"
//#include "imgui_impl_glfw_gl3.h"
#include "stb_image_write.h"
#include "AudioManager.h"
#include "Transform.h"
#include "AudioManager.h"
#include "TextureLoader.h"
#include "ShaderProgram.h"
#include "Box.h"
#include "Sprite.h"
#include <GLFW\glfw3.h>

bool Game::frameBufferSizeUpated;
float Game::deltaTime;
float Game::timeSinceStartUp;
std::unique_ptr<b2World> Game::world;
glm::vec2 Game::mouseCoord;

struct Game::InternalAcess
{
	std::chrono::steady_clock clockTime;
	GLFWwindow* window;
	GLFWcursor* cursor;
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};
Game::InternalAcess* Game::acess;
Game::Game(unsigned int screenWidth, unsigned int screenHeight, std::string title)
{
	world = std::make_unique<b2World>(b2Vec2(0, -9.81f));
	glfwInit();
	acess = new InternalAcess;
	acess->window = glfwCreateWindow(screenWidth, screenHeight, title.c_str(), NULL, NULL);
	if (acess->window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(acess->window);
	glfwSetInputMode(acess->window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetFramebufferSizeCallback(acess->window, acess->framebuffer_size_callback);

	GLenum err = glewInit();
	if (GLEW_OK != err)
		std::cout << "Error: %s\n" << glewGetErrorString(err);
	else
		std::cout << " Glew initialsed" << std::endl;
	//IMGUI_INIT(acess->window, true);
	YSE::System().init();
}
void Game::initialize()
{
	gameObjects = GameObject::getAllGameObjects();
	for (unsigned int i = 0; i < gameObjects.size(); i++)
	{
		std::vector<Component*> componentsAttachedToObject = gameObjects[i]->getAttachedComponents();
		if (camera == nullptr)
		{
			if (gameObjects[i]->hasComponent<Camera>())
				camera = gameObjects[i]->getComponent<Camera>();
		}
		for (unsigned int i = 0; i < componentsAttachedToObject.size(); i++)
			(*componentsAttachedToObject[i]).start();
	}
	if (camera == nullptr)
	{
		std::cout << "\nNo Camera Has Been Attached To An Object\nProviding Default Camera\n";
		camera = new Camera();
		int width, height;
		glfwGetWindowSize(acess->window, &width, &height);
		camera->init(glm::vec2(width, height));
	}
	std::stable_sort(gameObjects.begin(), gameObjects.end(), [](GameObject* a, GameObject* b)
	{return a->getLayerOrder() < b->getLayerOrder(); });
}
//ImVec4 clearColour;
void Game::update()
{
	ShaderProgram shaderProgram;
	shaderProgram.compileShaders("Test Resources\\spriteBase.vs", "Test Resources\\spriteBase.fs");
	shaderProgram.addAttribute("vertexPosition");
	shaderProgram.linkShaders();

	GLint textureLocation = shaderProgram.getUniformLocation("textureOne");
	GLint uniformProjectionMatrixLocation = shaderProgram.getUniformLocation("projection");
	GLint uniformModelMatrixLocation = shaderProgram.getUniformLocation("model");

	std::chrono::steady_clock::time_point start = acess->clockTime.now();
	std::chrono::steady_clock::time_point initialTime = acess->clockTime.now();
	deltaTime = 0.0f;
	timeSinceStartUp = 0.0f;

	while (!glfwWindowShouldClose(acess->window))
	{
		if (frameBufferSizeUpated)
		{
			int width, height;
			glfwGetWindowSize(acess->window, &width, &height);
			std::cout << "\nUpdated to : " << width << " ," << height;
			camera->setScreenRatio(glm::vec2(width, height));
			frameBufferSizeUpated = false;
		}
		YSE::System().update();
		if (gameObjects.size() != GameObject::getAllGameObjects().size())
		{
			GameObject* gameObjRef = GameObject::getAllGameObjects()[GameObject::getAllGameObjects().size() - 1];
			gameObjects.push_back(gameObjRef);
			std::vector<Component*> componentsAttachedToObject = gameObjRef->getAttachedComponents();
			for (unsigned int i = 0; i < componentsAttachedToObject.size(); i++)
				(*componentsAttachedToObject[i]).start();
			std::stable_sort(gameObjects.begin(), gameObjects.end(), [](GameObject* a, GameObject* b)
			{return a->getLayerOrder() < b->getLayerOrder(); });
		}

		//IMGUI_NEWFRAME();

		glClear(GL_COLOR_BUFFER_BIT);
		//processInput(window);

		/*for (unsigned int i = 0; i < gameObjects.size(); i++)
		{
			Transform * temp = gameObjects[i]->getComponent<Transform>();
			ImGui::Text("OBJECT : %s is at position = ( %.2f , %.2f ) | Rotation is : %.2f", gameObjects[i]->getName().c_str(),
				temp->position.x, temp->position.y, temp->rotation);
		}
		ImGui::ColorEdit3("BG COLOUR", (float*)&clearColour);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);*/

		//glClearColor(clearColour.x, clearColour.y, clearColour.z, 1.0f);
		glClearColor(0.25f, 0.45f, 0.15f, 1.0f);

		shaderProgram.use();
		glm::mat4 matrixTransform;
		glm::mat4 cameraMatrix = camera->getOrthoMatrix();
		glUniformMatrix4fv(uniformProjectionMatrixLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
		glUniform1i(textureLocation, 0);

		for (unsigned int i = 0; i < gameObjects.size(); i++)
		{
			Transform *transformRef = gameObjects[i]->getComponent<Transform>();
			if (gameObjects[i]->hasComponent<BoxCollider>())
			{
				BoxCollider* boxcolBody = gameObjects[i]->getComponent<BoxCollider>();
				transformRef->position = glm::vec2(boxcolBody->getPosition().x, boxcolBody->getPosition().y);
				transformRef->rotation = boxcolBody->getAngle();
			}
			std::vector<Component*> componentsAttachedToObject =
				GameObject::getGameObjectWithName(gameObjects[i]->getName())->getAttachedComponents();
			for (unsigned int i = 0; i < componentsAttachedToObject.size(); i++)
				(*componentsAttachedToObject[i]).update();
			if (camera->isObjectInCameraView(transformRef->position, transformRef->scale))
			{
				glUniformMatrix4fv(uniformModelMatrixLocation, 1, GL_FALSE, &(transformRef->getModelMatrix()[0][0]));
				if (gameObjects[i]->hasComponent<Sprite>())
					gameObjects[i]->getComponent<Sprite>()->draw();
			}
		}

		//TODO:
		//Make transform component automatically take care of it's physics
		//Maybe each sprite should have reference to it's transform( or modelMatrixLocation and shader used)
		//Attach frame buffer stuff and shader code for screen to camera
		//Shader manager stuff
		//gameobjects in game dynamic addition and deletion support
		shaderProgram.unuse();
		glBindTexture(GL_TEXTURE_2D, 0);
		//ImGui::Render();
		glfwSwapBuffers(acess->window);
		glfwPollEvents();

		std::chrono::duration<float> frameTime = acess->clockTime.now() - start;
		deltaTime = frameTime.count();
		world->Step(deltaTime, 4, 5);
		std::chrono::duration<float> sinceStart = acess->clockTime.now() - initialTime;
		timeSinceStartUp = sinceStart.count();

		start = acess->clockTime.now();
	}
	//glfwDestroyCursor(cursor);
	YSE::System().close();
	//IMGUI_SHUTDOWN();
	glfwTerminate();
	return;
}
void Game::setCursor(const std::string & cursorImagePath)
{
	std::vector<unsigned char>pixels;
	int w, h;
	TextureManager::getRawImageDataFromFile(cursorImagePath, pixels, w, h, false);

	GLFWimage image;
	image.width = w;
	image.height = h;
	image.pixels = &pixels[0];

	acess->cursor = glfwCreateCursor(&image, 0, 0);
	glfwSetCursor(acess->window, acess->cursor);
}
void Game::hideCursor(bool hide)
{
	if (hide)
		glfwSetInputMode(acess->window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	else
		glfwSetInputMode(acess->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
void Game::lockCursor(bool lock)
{
	if (lock)
		glfwSetInputMode(acess->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	else
		glfwSetInputMode(acess->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
bool pressed = false;

void Game::cleanUp()
{
	GameObject::removeAllGameObjectsFromMemory();
	AudioManager::removeLoadedAudioFromMemory();
	TextureManager::unloadTexturesFromMemory();
	if (acess->cursor != nullptr)
		glfwDestroyCursor(acess->cursor);
}

Game::~Game()
{
	if (acess != nullptr)
		delete acess;
}

bool Game::isKeyPressed(Key key)
{
	if (glfwGetKey(acess->window, (int)key) == GLFW_PRESS)
		return true;
	return false;
}
bool Game::isKeyReleased(Key key)
{
	if (glfwGetKey(acess->window, (int)key) == GLFW_RELEASE)
		return true;
	return false;
}
const glm::vec2* Game::getMouseCoords()
{
	double x, y;
	glfwGetCursorPos(acess->window, &x, &y);
	mouseCoord.x = (float)x;
	mouseCoord.y = (float)y;
	return &mouseCoord;
}
b2World* Game::getPhysicsWorld()
{
	return world.get();
}

void Game::InternalAcess::framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
	frameBufferSizeUpated = true;
}
