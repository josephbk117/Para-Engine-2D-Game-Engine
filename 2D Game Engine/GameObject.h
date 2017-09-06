#pragma once
#include "Sprite.h"
#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include <GL\glew.h>
#include <Box2D\Box2D.h>
#include "Box.h"
#include "ShaderProgram.h"
class GameObject
{
public:
	GameObject(b2World *world, glm::vec2 position, glm::vec2 dimensions, b2BodyType bodyType);
	~GameObject();
	Sprite sprite;
	Box boxCollider;
	void drawObject(ShaderProgram &shader);
};

