#pragma once
class Component
{
public:
	virtual void start() { };
	virtual void update() { };
	virtual ~Component() {};
protected:
	Component(void) {}
};