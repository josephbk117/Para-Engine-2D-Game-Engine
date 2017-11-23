#pragma once
class GuiComponent;
#include "GuiElement.h"
class GuiComponent
{
public:
	virtual void start() { };
	virtual void update() { };
	GuiComponent() { };
	GuiElement* attachedGuiObject = nullptr;
	virtual ~GuiComponent() {};
};
