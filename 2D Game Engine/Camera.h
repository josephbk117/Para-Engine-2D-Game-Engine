#pragma once
#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include "Component.h"
#include "Transform.h"

class Camera : public Component
{
public:
	Camera();
	~Camera();
	void init(glm::vec2 screenDimensions);
	virtual void start();
	virtual void update();
	void setScale(float newScale);
	float getScale()const;
	glm::mat4 getOrthoMatrix()const;
	bool isObjectInCameraView(const glm::vec2 & position, const glm::vec2& dimensions)const;
	void setScreenRatio(glm::vec2 screenDimension);
private:
	glm::vec2 screenDimensions;
	bool needsUpdate;
	Transform* transform;
	Transform previousTransformData;
	glm::mat4 orthographicMatrix;
	glm::mat4 viewMatrix;
	float scale;
};