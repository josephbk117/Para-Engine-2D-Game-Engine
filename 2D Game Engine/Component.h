#pragma once
#include <iostream>
class Component
{
public:
	virtual void start() { std::cout << "\n\t\tBase START FUNC"; };
	virtual void update() { std::cout << "\n\t\tBase UPDATE FUNC"; };
	virtual ~Component() {};
protected:
	Component(void) {}
};