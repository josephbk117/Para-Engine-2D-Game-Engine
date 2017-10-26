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
	void compileShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	void linkShaders();
	void addAttribute(const std::string& attributeName);
	void use();
	void unuse();
	GLint getUniformLocation(const std::string& uniformName)const;
private:
	GLuint programID, vertexShaderID, fragmentShaderID;
	void compileShader(const std::string& filePath, GLuint ID);
	int attributeCount;
};

