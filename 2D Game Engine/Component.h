#pragma once
class Component
{
public:
	void start() {};
	void update() {};
	virtual ~Component() {};
protected:
	Component(void) {}
};