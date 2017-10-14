#include "GameObject.h"

GameObject::GameObject(b2World *world, glm::vec2 position, glm::vec2 dimensions, b2BodyType bodyType, float density)
{
	sprite.init(0, 0, dimensions.x, dimensions.y);
	boxCollider.init(world, position, dimensions, bodyType, density);
	name = "";
}

GameObject::~GameObject()
{
}

glm::vec2 GameObject::getPosition()
{
	return glm::vec2(this->boxCollider.getBody()->GetPosition().x,
		this->boxCollider.getBody()->GetPosition().y);
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
	modelMat = glm::translate(modelMat, glm::vec3(this->boxCollider.getBody()->GetPosition().x,
		this->boxCollider.getBody()->GetPosition().y, 0));
	glUniformMatrix4fv(uniformModelMatrixLocation, 1, GL_FALSE, &(modelMat[0][0]));
	sprite.draw();
}
