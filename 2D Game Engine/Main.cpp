#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include "Game.h"

int main(int argc, char* argv[])
{
	Game game(600, 600, "2D Game Engine");
	game.initialize();
	game.update();
	return 0;
}
