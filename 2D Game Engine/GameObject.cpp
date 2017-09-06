#include "GameObject.h"


GameObject::GameObject(b2World *world,glm::vec2 position, glm::vec2 dimensions, b2BodyType bodyType)
{
	sprite.init(position.x, position.y, dimensions.x, dimensions.y);
	boxCollider.init(world, position, dimensions, bodyType);
}


GameObject::~GameObject()
{
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
