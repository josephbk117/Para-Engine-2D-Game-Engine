#include<GL\glew.h>
#include<GLFW\glfw3.h>
#include<iostream>
#include "Game.h"

#define SCR_WIDTH 600
#define SCR_HEIGHT 480

void drawOnUpdate();

int main(int argc, char* argv[])
{
	Game game(600, 400, "2D Game Engine");
	game.update(drawOnUpdate);
	return 0;
}
void drawOnUpdate()
{
	glPointSize(10);
	glBegin(GL_QUADS);
	glVertex2f(-30, 30);
	glVertex2f(30, 30);
	glVertex2f(30, -30);
	glVertex2f(-30, -30);
	glEnd();
}
