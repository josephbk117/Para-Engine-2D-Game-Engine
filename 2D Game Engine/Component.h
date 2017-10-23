#pragma once
#include <iostream>
class Component
{
public:
	virtual void start() { };
	virtual void update() { };
	virtual ~Component() {};
protected:
	Component(void) {}
};