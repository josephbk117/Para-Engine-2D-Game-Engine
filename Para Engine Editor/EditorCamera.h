#pragma once
#include <ParaEngine/Transform.h>
#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>
class EditorCamera
{
public:
	EditorCamera();
	~EditorCamera();
	void setDimension(float dimensionX, float dimensionY) noexcept;
	void setDimension(const glm::vec2& screenDimensions)noexcept;
	void setScale(float newScale);
	const float& getScale()const noexcept;
	void setPosition(float x, float y);
	void setRotation(float radians);
	glm::vec2 getPosition();
	float getRotation();
	const glm::mat4& getOrthoMatrix()const noexcept;
	void setScreenRatio(const glm::vec2& screenDimension) noexcept;
	const glm::vec2 convertScreenPointToWorldPoint(const glm::vec2& screenPosition, const glm::vec2& screenDimensions) noexcept;
	void update();
private:
	glm::vec2 screenDimensions;
	bool needsUpdate = true;
	Transform transform;
	Transform previousTransformData;
	glm::mat4 orthographicMatrix;
	glm::mat4 viewMatrix;
	float scale;
};