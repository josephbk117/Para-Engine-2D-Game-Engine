#pragma once
#include <string>
#include "GameObject.h"
#include "Sprite.h"
#include "Transform.h"
class GuiElement;
#include "Component.h"
class GuiElement : private GameObject
{
public:
	GuiElement();
	~GuiElement();

	void setScreenLocation(const glm::vec2& screenPosition) { transform.setPosition(screenPosition); transform.update(); };
	const glm::vec2& getScreenLocation()const { return transform.getPosition(); };
	glm::mat4 getMatrix()const { return transform.getMatrix(); };
	void addGuiComponent(Component* component);
	const std::vector<Component *>& getAttachedComponents() { return guiComponents; };
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
	template<class T>
	T* const getGuiComponent(void)const;

private:
	Transform transform;
	std::vector<Component *> guiComponents;
	static std::vector<GuiElement *> guiElementVector;
};

template<class T>
inline T* const GuiElement::getGuiComponent(void)const
{
	const unsigned int sizeValue = guiComponents.size();
	for (unsigned int i = 0; i < sizeValue; i++)
	{
		if (typeid(*guiComponents[i]) == typeid(T))
			return (T *)guiComponents[i];
	}
	return nullptr;
}

