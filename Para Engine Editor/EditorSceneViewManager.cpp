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
	Camera* editorCamera = nullptr;
	if (!doneOnce)
	{
		shaderGameObjectsBase.compileShaders("Test Resources\\spriteBase.vs", "Test Resources\\spriteBase.fs");
		shaderGameObjectsBase.addAttribute("vertexPosition");
		shaderGameObjectsBase.linkShaders();

		textureGameObjectLocation = shaderGameObjectsBase.getUniformLocation("textureOne");
		uniformProjectionMatrixGameObjectLocation = shaderGameObjectsBase.getUniformLocation("projection");
		uniformModelMatrixGameObjectLocation = shaderGameObjectsBase.getUniformLocation("model");
		doneOnce = true;

	}
	editorCameraObject.getComponent<Transform>()->update();
	editorCamera->update();
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
	ShaderProgram::applyShaderUniformMatrix(uniformProjectionMatrixGameObjectLocation, editorCamera->getOrthoMatrix());
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
	if (io.MouseDoubleClicked[0])
	{
		editorCameraObject.getComponent<Camera>()->setScale(editorCameraObject.getComponent<Camera>()->getScale() + 0.5f);
	}
}
