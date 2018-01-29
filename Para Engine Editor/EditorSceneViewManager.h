#pragma once
#include <Game.h>
#include <Camera.h>
#include <ShaderProgram.h>
#include <GL\glew.h>
#include <GameObject.h>
#include "EditorCamera.h"
class EditorSceneViewManager
{
public:
	static EditorSceneViewManager instance;
	EditorCamera editorCamera;
	EditorSceneViewManager();
	~EditorSceneViewManager();
	void updateSceneView();
	void handleInput();
private:
	std::vector<GameObject *> gameObjects;
	ShaderProgram shaderGameObjectsBase;
	GLint textureGameObjectLocation;
	GLint uniformProjectionMatrixGameObjectLocation;
	GLint uniformModelMatrixGameObjectLocation;
};