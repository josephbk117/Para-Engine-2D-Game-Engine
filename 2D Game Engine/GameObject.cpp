#include "GameObject.h"

GameObject::GameObject(b2World *world, glm::vec2 position, glm::vec2 dimensions, b2BodyType bodyType, float density)
{
	sprite.init(0, 0, dimensions.x, dimensions.y);
	boxCollider.init(world, position, dimensions, bodyType, density);
	name = "NULL";
}

GameObject::~GameObject()
{
}

glm::vec2 GameObject::getPosition()
{
	return glm::vec2(boxCollider.getBody()->GetPosition().x, boxCollider.getBody()->GetPosition().y);
}

void GameObject::setPosition(float x, float y)
{
	boxCollider.getBody()->SetTransform(b2Vec2(x, y), 0.0f);
}

void GameObject::setName(const std::string & name)
{
	this->name = name;
}

std::string GameObject::getName()
{
	return name;
}

void GameObject::drawObject(ShaderProgram &shaderProgram)
{
	GLint uniformModelMatrixLocation = shaderProgram.getUniformLocation("model");
	glm::mat4 modelMat;
	modelMat = glm::mat4(1);
	modelMat = glm::translate(modelMat, glm::vec3(boxCollider.getBody()->GetPosition().x,
		boxCollider.getBody()->GetPosition().y, 0));
	modelMat = glm::rotate(modelMat, boxCollider.getBody()->GetAngle(), glm::vec3(0, 0, 1.0f));
	glUniformMatrix4fv(uniformModelMatrixLocation, 1, GL_FALSE, &(modelMat[0][0]));
	sprite.setTextureID(textureID);
	sprite.draw();
}

void GameObject::setTextureID(unsigned int textureID)
{
	this->textureID = textureID;
}

void GameObject::setObjectVelocity(float x, float y)
{
	boxCollider.getBody()->SetLinearVelocity(b2Vec2(x, y));
}

void GameObject::setAngularVelocity(float value)
{
	boxCollider.getBody()->SetAngularVelocity(value);
}

void GameObject::translate(glm::vec2 translation)
{
	boxCollider.getBody()->SetAwake(false);
	setPosition(getPosition().x + translation.x, getPosition().y + translation.y);
	boxCollider.getBody()->SetAwake(true);
}
