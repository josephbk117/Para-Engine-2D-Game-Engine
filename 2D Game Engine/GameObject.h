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
	GameObject(b2World *world, glm::vec2 position, glm::vec2 dimensions, b2BodyType bodyType,float density);
	~GameObject();
	Sprite sprite;
	Box boxCollider;
	glm::vec2 getPosition();
	void setPosition(float x, float y);
	void setName(const std::string& name);
	std::string getName();
	void drawObject(ShaderProgram &shader);
	void setTextureID(unsigned int textureID);
	void setObjectVelocity(float x, float y);
	void setAngularVelocity(float value);
	void translate(glm::vec2 translation);
private:
	std::string name;
	unsigned int textureID;
};

