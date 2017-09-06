#include "GameObject.h"


GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::drawObject(ShaderProgram &shaderProgram)
{
	GLint uniformModelMatrixLocation = shaderProgram.getUniformLocation("model");
	glm::mat4 modelMat;
	modelMat = glm::mat4(1.0);
	modelMat = glm::translate(modelMat, glm::vec3(this->boxCollider.getBody()->GetPosition().x,
		this->boxCollider.getBody()->GetPosition().y, 0));
	glUniformMatrix4fv(uniformModelMatrixLocation, 1, GL_FALSE, &(modelMat[0][0]));

	sprite.setPosition(glm::vec2(boxCollider.getBody()->GetPosition().x, boxCollider.getBody()->GetPosition().y));
	sprite.draw();
}
