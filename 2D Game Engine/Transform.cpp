#include "Transform.h"
glm::mat4 Transform::getModelMatrix()
{
	return modelMatrix;
}
void Transform::update()
{
	setModelMatrix();
}
void Transform::setModelMatrix()
{
	modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0));
	modelMatrix = glm::rotate(modelMatrix, rotation, glm::vec3(0, 0, 1.0f));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(scale.x, scale.y, 0));
}
