#pragma once
#include <iostream>
#include <GL\glew.h>
#include <fstream>
#include <string>
class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();
	void compileShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	void linkShaders();
private:
	GLuint programID, vertexShaderID, fragmentShaderID;
};

