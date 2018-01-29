#include "EditorSceneViewManager.h"
#include "ResourceManager.h"
#include "imgui.h"
#include <ShaderProgram.h>
#include <Sprite.h>
#include <Box.h>
#include <Camera.h>
#include <GL\glew.h>
#include <iostream>

EditorSceneViewManager EditorSceneViewManager::instance;
EditorSceneViewManager::EditorSceneViewManager() {}
EditorSceneViewManager::~EditorSceneViewManager() {}

void EditorSceneViewManager::updateSceneView()
{
	static bool doneOnce = false;
	if (!doneOnce)
	{
		shaderGameObjectsBase.compileShaders("Test Resources\\spriteBase.vs", "Test Resources\\spriteBase.fs");
		shaderGameObjectsBase.addAttribute("vertexPosition");
		shaderGameObjectsBase.linkShaders();

		textureGameObjectLocation = shaderGameObjectsBase.getUniformLocation("textureOne");
		uniformProjectionMatrixGameObjectLocation = shaderGameObjectsBase.getUniformLocation("projection");
		uniformModelMatrixGameObjectLocation = shaderGameObjectsBase.getUniformLocation("model");
		doneOnce = true;
		editorCamera.setDimension(3.0f, 3.0f);

	}
	editorCamera.update();
	if (GameObject::isDirty)
	{
		GameObject::isDirty = false;
		GameObject::removeAllObjectsMarkedForDeletion();
		gameObjects = GameObject::getAllGameObjects();
		unsigned int sizeValue = gameObjects.size();
		for (unsigned int i = 0; i < sizeValue; i++)
		{
			GameObject* gameObjRef = gameObjects[i];
			if (!gameObjRef->hasStartBeenCalled)
			{
				gameObjRef->hasStartBeenCalled = true;
				std::vector<Component*> componentsAttachedToObject = gameObjRef->getAttachedComponents();
				unsigned int componentCount = componentsAttachedToObject.size();
				for (unsigned int i = 0; i < componentCount; i++)
					(*componentsAttachedToObject[i]).start();
			}
		}
		std::stable_sort(gameObjects.begin(), gameObjects.end(), [](GameObject* a, GameObject* b)
		{return a->getLayerOrder() < b->getLayerOrder(); });
	}

	std::vector<GameObject *> uiGameobjs;
	shaderGameObjectsBase.use();
	ShaderProgram::applyShaderUniformMatrix(uniformProjectionMatrixGameObjectLocation, editorCamera.getOrthoMatrix());
	glUniform1i(textureGameObjectLocation, 0);
	for (unsigned int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->isPartOfUI)
			uiGameobjs.push_back(gameObjects[i]);
		else
		{
			Transform *transformRef = gameObjects[i]->getComponent<Transform>();
			BoxCollider* boxcolBody = gameObjects[i]->getComponent<BoxCollider>();
			if (boxcolBody != nullptr)
			{
				transformRef->setPosition(glm::vec2(boxcolBody->getPosition().x, boxcolBody->getPosition().y));
				transformRef->setRotation(boxcolBody->getAngle());
			}
			std::vector<Component*> componentsAttachedToObject =
				GameObject::getGameObjectWithName(gameObjects[i]->getName())->getAttachedComponents();
			for (unsigned int i = 0; i < componentsAttachedToObject.size(); i++)
				(*componentsAttachedToObject[i]).update();
			ShaderProgram::applyShaderUniformMatrix(uniformModelMatrixGameObjectLocation, transformRef->getWorldSpaceTransform());
			Sprite* spriteToDraw = gameObjects[i]->getComponent<Sprite>();
			if (spriteToDraw != nullptr)
				spriteToDraw->draw();
		}
	}
}

void EditorSceneViewManager::handleInput()
{
	ImGuiIO& io = ImGui::GetIO();
	float xV = 0, yV = 0;
	if (io.KeyAlt)
	{
		if (io.KeysDown[(int)Key::W])
			yV = 0.01f;
		if (io.KeysDown[(int)Key::S])
			yV = -0.01f;
		if (io.KeysDown[(int)Key::A])
			xV -= 0.01f;
		if (io.KeysDown[(int)Key::D])
			xV = 0.01f;
	}
	editorCamera.setPosition(editorCamera.getPosition().x + xV, editorCamera.getPosition().y + yV);
}
