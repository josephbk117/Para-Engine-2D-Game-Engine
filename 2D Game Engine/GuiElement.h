#pragma once
#include <string>
#include "Sprite.h"
#include "Transform.h"
class GuiElement;
#include "GuiComponent.h"
class GuiElement
{
public:
	GuiElement();
	~GuiElement();

	void init(const glm::vec2& dimensions, unsigned int textureID) { uiSprite.init(dimensions.x*2.0f, dimensions.y*2.0f); uiSprite.setTextureID(textureID); };
	void setTextureID(unsigned int textureID) { uiSprite.setTextureID(textureID); };

	void setScreenLocation(const glm::vec2& screenPosition) { transform.setPosition(screenPosition); transform.update(); };
	const glm::vec2& getScreenLocation()const { return transform.getPosition(); };
	void setDimensions(const glm::vec2& dimension) { uiSprite.setDimension(dimension); };
	glm::vec2 getDimensions()const { return uiSprite.getDimensions(); };
	void draw() { uiSprite.draw(); }
	glm::mat4 getMatrix()const { return transform.getMatrix(); };
	void addGuiComponent(GuiComponent* component);
	const std::vector<GuiComponent *>& getAttachedComponents() { return guiComponents; };
	static GuiElement* createGuiElement(const std::string& name)
	{
		GuiElement* guiObject = new GuiElement;
		guiElementVector.push_back(guiObject);
		return guiObject;
	}
	static std::vector<GuiElement *> getAllGuiElements()
	{
		return guiElementVector;
	}

private:
	Sprite uiSprite;
	Transform transform;
	static std::vector<GuiElement *> guiElementVector;
	std::vector<GuiComponent *> guiComponents;
};

