#include "EditorCamera.h"

using namespace glm;
EditorCamera::EditorCamera()
{
	orthographicMatrix = mat4(1.0f);
	viewMatrix = mat4(1.0f);
	scale = 1.0f;
	screenDimensions = vec2(500, 500);
}

EditorCamera::~EditorCamera()
{
}

void EditorCamera::setDimension(float dimensionX, float dimensionY) noexcept
{
	this->screenDimensions = glm::vec2(dimensionX, dimensionY);
	orthographicMatrix = ortho(-((float)dimensionX / 2.0f), ((float)dimensionX / 2.0f),
		-((float)dimensionY / 2.0f), ((float)dimensionY / 2.0f));
	needsUpdate = true;
}

void EditorCamera::setDimension(const glm::vec2 & screenDimensions) noexcept
{
	setDimension(screenDimensions.x, screenDimensions.y);
}

void EditorCamera::setScale(float newScale)
{
	needsUpdate = true;
	scale = newScale;
}

const float & EditorCamera::getScale() const noexcept
{
	return scale;
}

void EditorCamera::setPosition(float x, float y)
{
	transform.setPosition(x, y);
}

void EditorCamera::setRotation(float radians)
{
	transform.setRotation(radians);
}

glm::vec2 EditorCamera::getPosition()
{
	return transform.getPosition();
}

float EditorCamera::getRotation()
{
	return transform.getRotation();
}

const glm::mat4 & EditorCamera::getOrthoMatrix() const noexcept
{
	return viewMatrix;
}

void EditorCamera::setScreenRatio(const glm::vec2 & screenDimension) noexcept
{
	float aspect = (float)screenDimension.x / (float)screenDimension.y;

	orthographicMatrix = ortho(-((float)screenDimensions.x / 2.0f) * aspect,
		((float)screenDimensions.x / 2.0f) * aspect,
		-((float)screenDimensions.y / 2.0f),
		((float)screenDimensions.y / 2.0f));
	needsUpdate = true;
}

const glm::vec2 EditorCamera::convertScreenPointToWorldPoint(const glm::vec2 & screenPosition, const glm::vec2 & screenDimensions) noexcept
{
	mat4 model = translate(mat4(1.0f), glm::vec3(-transform.getPosition().x, transform.getPosition().y, 0.0f));
	model = rotate(model, -transform.getRotation(), glm::vec3(0, 0, 1.0f));
	vec4 viewport(0.0f, 0.0f, screenDimensions.x, screenDimensions.y);
	vec3 unprojected = glm::unProject(glm::vec3(screenPosition.x, screenPosition.y, 0.0f), model, orthographicMatrix, viewport);
	return glm::vec2(unprojected.x, -unprojected.y);
}

void EditorCamera::update()
{
	if (transform != previousTransformData || needsUpdate)
	{
		previousTransformData = transform;
		viewMatrix = glm::scale(orthographicMatrix, vec3(scale, scale, 0.0f));
		viewMatrix = glm::rotate(viewMatrix, transform.getRotation(), glm::vec3(0.0f, 0.0f, 1));
		viewMatrix = glm::translate(viewMatrix, vec3(-transform.getPosition().x, -transform.getPosition().y, 0));
		if (needsUpdate)
			needsUpdate = false;
	}
}
