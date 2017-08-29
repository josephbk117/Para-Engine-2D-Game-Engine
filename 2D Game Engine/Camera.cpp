#include "Camera.h"

Camera::Camera()
{
	position = vec2(0.0f, 0.0f);
	orthoMatrix = mat4(1.0f);
	viewMatrix = mat4(1.0f);
	scale = 1.0f;
	needsUpdate = true;
	screenDimensions = vec2(500, 500);
}


Camera::~Camera()
{
}

void Camera::init(vec2 screenDimensions)
{
	this->screenDimensions = screenDimensions;
	orthoMatrix = ortho(0.0f, screenDimensions.x, 0.0f, screenDimensions.y);
}

void Camera::setPosition(const vec2& newPosition)
{
	position = newPosition;
}

vec2 Camera::getPosition()
{
	return position;
}

void Camera::setScale(float newScale)
{
	scale = newScale;
}

float Camera::getScale()
{
	return scale;
}

mat4 Camera::getOrthoMatrix()
{
	return orthoMatrix;
}

void Camera::update()
{
	if (needsUpdate)
	{
		viewMatrix = translate(orthoMatrix, vec3(-position.x, -position.y, 0));
	}
}
