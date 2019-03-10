#pragma once
#include <GL\glew.h>
#include <ParaEngine/Game.h>
#include <ParaEngine/Camera.h>
#include <ParaEngine/ShaderProgram.h>
#include <ParaEngine/GameObject.h>
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