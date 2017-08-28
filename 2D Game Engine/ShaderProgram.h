#pragma once
#include <string>
class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();
	void compileShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	void linkShaders();
};

