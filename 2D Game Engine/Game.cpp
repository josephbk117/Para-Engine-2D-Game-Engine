#include "Game.h"
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include <random>
#include <typeinfo>
#include "stb_image_write.h"
bool Game::frameBufferSizeUpated;
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
	// Setup ImGui binding
	IMGUI_INIT(window, true);
	GameObject* tempGameObject;

	unsigned int texVal1 = TextureLoader::loadTextureFromFile("Test Resources\\frasa.png", false);
	unsigned int texVal2 = TextureLoader::loadTextureFromFile("Test Resources\\mamma.png", false);

	tempGameObject = GameObject::createGameObject("Sammy");
	tempGameObject->addComponent(new Transform(glm::vec2(0, 0), 00.0f, glm::vec2(1, 1)));
	Sprite * tempSprite = new Sprite();
	tempSprite->init(0, 0, 50, 50);
	tempSprite->setTextureID(texVal1);
	tempGameObject->addComponent(tempSprite);
	gameObjects.push_back(tempGameObject);

	tempGameObject = GameObject::createGameObject("Lola");
	tempGameObject->setLayerOrder(10);
	tempGameObject->addComponent(new Transform(glm::vec2(-50, -100), 0.0f, glm::vec2(1, 1)));
	tempSprite = new Sprite();
	tempSprite->init(0, 0, 80, 80);
	tempSprite->setTextureID(texVal1);
	tempGameObject->addComponent(tempSprite);
	gameObjects.push_back(tempGameObject);

	tempGameObject = GameObject::createGameObject("Babu");
	tempGameObject->addComponent(new Transform(glm::vec2(-120, -100), 0.0f, glm::vec2(1, 1)));
	tempSprite = new Sprite();
	tempSprite->init(0, 0, 80, 80);
	tempSprite->setTextureID(texVal1);
	tempGameObject->addComponent(tempSprite);
	Box* boxCollider = new Box();
	boxCollider->init(world.get(), tempGameObject->getComponent<Transform>()->position, glm::vec2(80, 80), b2BodyType::b2_dynamicBody, 1.0f);
	tempGameObject->addComponent(boxCollider);
	gameObjects.push_back(tempGameObject);

	tempGameObject = GameObject::createGameObject("Galoo");
	tempGameObject->addComponent(new Transform(glm::vec2(-120, -250), 0.0f, glm::vec2(1, 1)));
	tempSprite = new Sprite();
	tempSprite->init(0, 0, 300, 50);
	tempSprite->setTextureID(texVal2);
	tempGameObject->addComponent(tempSprite);
	boxCollider = new Box();
	boxCollider->init(world.get(), tempGameObject->getComponent<Transform>()->position,
		glm::vec2(300, 50), b2BodyType::b2_staticBody, 1.0f);
	tempGameObject->addComponent(boxCollider);
	gameObjects.push_back(tempGameObject);
	std::stable_sort(gameObjects.begin(), gameObjects.end(), [](GameObject* a, GameObject* b) {return a->getLayerOrder() < b->getLayerOrder(); });

	std::vector<Component*> componentsAttachedToGaloo = GameObject::getGameObjectWithName("Galoo")->getAttachedComponents();
	camera.init(glm::vec2(600, 600));
	camera.setPosition(glm::vec2(0, 0));
}
ImVec4 clearColour;
//Pass in a function to be run every frame
float loll = 0;

void Game::update(void(*updateFunc)())
{
	ShaderProgram shaderProgram;
	shaderProgram.compileShaders("Test Resources\\spriteBase.vs", "Test Resources\\spriteBase.fs");
	shaderProgram.addAttribute("vertexPosition");
	shaderProgram.linkShaders();

	GLint textureLocation = shaderProgram.getUniformLocation("textureOne");
	GLint uniformProjectionMatrixLocation = shaderProgram.getUniformLocation("projection");
	GLint uniformModelMatrixLocation = shaderProgram.getUniformLocation("model");

	Sprite bgSprite;
	bgSprite.init(0, 0, 800, 700);
	unsigned int texVal3 = TextureLoader::loadTextureFromFile("Test Resources\\lili.jpg", false);
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
		std::chrono::steady_clock::time_point start = clockTime.now();
		glClear(GL_COLOR_BUFFER_BIT);
		processInput(window);
		camera.update();
		//updateFunc();

		for (unsigned int i = 0; i < gameObjects.size(); i++)
		{
			Transform * temp = gameObjects[i]->getComponent<Transform>();
			ImGui::Text("OBJECT : %s is at position = ( %.2f , %.2f ) | Rotation is : %.2f", gameObjects[i]->getName().c_str(),
				temp->position.x, temp->position.y, temp->rotation);
		}
		ImGui::ColorEdit3("BG COLOUR", (float*)&clearColour);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		glClearColor(clearColour.x, clearColour.y, clearColour.z, 1.0f);

		bgSprite.setDimension(glm::vec2(600 + 50 * sin(loll), 600 + 50 * cos(loll)));
		GameObject::getGameObjectWithName("Sammy")->getComponent<Transform>()->rotation = loll;

		std::chrono::duration<float> frameTime = clockTime.now() - start;
		world->Step(frameTime.count() * 10, 5, 6);
		loll += frameTime.count() * 10;
		shaderProgram.use();

		glm::mat4 matrixTransform;

		glm::mat4 cameraMatrix = camera.getOrthoMatrix();
		glUniformMatrix4fv(uniformProjectionMatrixLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
		glUniform1i(textureLocation, 0);
		bgSprite.setTextureID(texVal3);
		matrixTransform = glm::translate(matrixTransform, glm::vec3(0, 0, 0));
		glUniformMatrix4fv(uniformModelMatrixLocation, 1, GL_FALSE, &(matrixTransform[0][0]));
		bgSprite.draw();
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
		GameObject::getGameObjectWithName("Lola")->getComponent<Transform>()->position.y += 1.0f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		GameObject::getGameObjectWithName("Lola")->getComponent<Transform>()->position.y -= 1.0f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		GameObject::getGameObjectWithName("Lola")->getComponent<Transform>()->position.x -= 1.0f;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		GameObject::getGameObjectWithName("Lola")->getComponent<Transform>()->position.x += 1.0f;
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS);
	//gameObjects[0]->setAngularVelocity(-10.0f);
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS);
	//gameObjects[0]->setAngularVelocity(10.0f);
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
