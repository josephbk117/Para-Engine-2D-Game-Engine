#pragma once
#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>
using namespace glm;
class Camera
{
public:
	Camera();
	~Camera();
	void init(vec2 screenDimensions);
	void setPosition(const vec2& newPosition);
	vec2 getPosition();
	void setScale(float newScale);
	float getScale();
	mat4 getOrthoMatrix();
	void update();
	bool isObjectInCameraView(const vec2 & position, const vec2 dimensions);
private:
	vec2 screenDimensions;
	bool needsUpdate;
	vec2 position;
	mat4 orthoMatrix;
	mat4 viewMatrix;
	float scale;

};